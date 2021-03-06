#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <getopt.h>
#include <atomic>
#include <signal.h>
#include <unistd.h>
#include <limits>
#include <unordered_map>

#include <zcm/zcm-cpp.hpp>

#include "zcm/json/json.h"

#include "util/TimeUtil.hpp"

using namespace std;

static atomic_int done {0};

static void sighandler(int signal)
{
    done++;
    if (done == 3) exit(1);
}

struct Args
{
    double speed = 1.0;
    bool verbose = false;
    string zcmUrlOut = "";
    string filename = "";
    string jslpFilename = "";
    zcm::Json::Value jslpRoot;
    string outfile = "";

    bool init(int argc, char *argv[])
    {
        struct option long_opts[] = {
            { "help",          no_argument, 0, 'h' },
            { "output",  required_argument, 0, 'o' },
            { "speed",   required_argument, 0, 's' },
            { "zcm-url", required_argument, 0, 'u' },
            { "jslp",    required_argument, 0, 'j' },
            { "verbose",       no_argument, 0, 'v' },
            { 0, 0, 0, 0 }
        };

        int c;
        while ((c = getopt_long(argc, argv, "ho:s:u:j:v", long_opts, 0)) >= 0) {
            switch (c) {
                case 'o':      outfile = string(optarg);       break;
                case 's':        speed = strtod(optarg, NULL); break;
                case 'u':    zcmUrlOut = string(optarg);       break;
                case 'j': jslpFilename = string(optarg);       break;
                case 'v':      verbose = true;                 break;
                case 'h': default: usage(); return false;
            };
        }

        if (optind != argc - 1) {
            cerr << "Please specify a logfile" << endl;
            usage();
            return false;
        }

        filename = string(argv[optind]);

        ifstream jslpFile { jslpFilename != "" ? jslpFilename : filename + ".jslp" };
        if (jslpFile.good()) {
            zcm::Json::Reader reader;
            if (!reader.parse(jslpFile, jslpRoot, false)) {
                if (verbose) {
                    cerr << "Failed to parse jslp file " << endl;
                    cerr << reader.getFormattedErrorMessages() << endl;
                }
                return false;
            }
            if (outfile != "") speed = 0;
            cerr << "Found jslp file. Filtering output." << endl;
        } else if (jslpFilename == "") {
            cerr << "No jslp file specified" << endl;
            if (outfile != "") {
                cerr << "Output file specified, but no jslp filter metafile found." << endl;
                return false;
            }
        } else {
            cerr << "Unable to find specified jslp file: " << jslpFilename << endl;
            return false;
        }

        if (speed == 0) speed = std::numeric_limits<decltype(speed)>::infinity();

        return true;
    }

    void usage()
    {
        cerr << "usage: zcm-logplayer [options] [FILE]" << endl
             << "" << endl
             << "    Reads packets from an ZCM log file and publishes them to a " << endl
             << "    ZCM transport." << endl
             << "" << endl
             << "Options:" << endl
             << "" << endl
             << "  -s, --speed=NUM        Playback speed multiplier.  Default is 1." << endl
             << "  -u, --zcm-url=URL      Play logged messages on the specified ZCM URL." << endl
             << "  -o, --output=filename  Instead of broadcasting over zcm, log directly " << endl
             << "                         to a file. Enabling this, ignores the" << endl
             << "                         \"--speed\" option" << endl
             << "  -j, --jslp=filename    Use this jslp meta file. " << endl
             << "                         If unspecified, zcm-logplayer looks for a file " << endl
             << "                         with the same filename as the input log and " << endl
             << "                         a .jslp suffix" << endl
             << "  -v, --verbose          Print information about each packet." << endl
             << "  -h, --help             Shows some help text and exits." << endl
             << endl;
    }
};

struct LogPlayer
{
    Args args;
    zcm::LogFile *zcmIn  = nullptr;
    zcm::ZCM     *zcmOut = nullptr;
    zcm::LogFile *logOut = nullptr;

    enum class StartMode { CHANNEL, US_DELAY, NUM_MODES };
    StartMode startMode = StartMode::NUM_MODES;
    string startChan = "";
    uint64_t startDelayUs = 0;

    bool filtering;

    enum class FilterType { CHANNELS, NUM_TYPES };
    FilterType filterType;

    enum class FilterMode { WHITELIST, BLACKLIST, SPECIFIED, NUM_MODES };
    FilterMode filterMode;

    unordered_map<string, bool> channelMap;

    LogPlayer() { }

    ~LogPlayer()
    {
        if (logOut) { logOut->close(); delete logOut; }
        if (zcmIn)  { delete zcmIn;                   }
        if (zcmOut) { delete zcmOut;                  }
    }

    bool init(int argc, char *argv[])
    {
        if (!args.init(argc, argv))
            return false;

        zcmIn = new zcm::LogFile(args.filename, "r");
        if (!zcmIn->good()) {
            cerr << "Error: Failed to open '" << args.filename << "'" << endl;
            return false;
        }

        if (args.outfile == "") {
            zcmOut = new zcm::ZCM(args.zcmUrlOut);
            if (!zcmOut->good()) {
                cerr << "Error: Failed to create output ZCM" << endl;
                return false;
            }

            cout << "Using playback speed " << args.speed << endl;
        } else {
            logOut = new zcm::LogFile(args.outfile, "w");
            if (!logOut->good()) {
                cerr << "Error: Failed to create output log" << endl;
                return false;
            }
        }

        if (args.jslpRoot.isMember("START")) {
            string startModeStr = args.jslpRoot["START"]["mode"].asString();
            if (!args.jslpRoot["START"].isMember("mode")) {
                cerr << "Start mode unspecified in jslp" << endl;
                return false;
            }
            if (startModeStr == "channel") {
                startMode = StartMode::CHANNEL;
                if (!args.jslpRoot["START"].isMember("channel")) {
                    cerr << "Start channel unspecified in jslp" << endl;
                    return false;
                }
                startChan = args.jslpRoot["START"]["channel"].asString();
                cout << "Starting after first message published on channel: "
                     << startChan << endl;
            } else if (startModeStr == "us_delay") {
                startMode = StartMode::US_DELAY;
                if (!args.jslpRoot["START"].isMember("us_delay")) {
                    cerr << "Start us_delay unspecified in jslp" << endl;
                    return false;
                }
                startDelayUs = args.jslpRoot["START"]["us_delay"].asUInt64();
                cout << "Starting after " << startDelayUs << " microseconds" << endl;
            } else {
                cerr << "Start mode unrecognized in jslp: " << startModeStr << endl;
                return false;
            }
        }

        filtering = args.jslpRoot.isMember("FILTER");
        if (filtering) {
            if (!args.jslpRoot["FILTER"].isMember("type")) {
                cerr << "Filter \"type\" in jslp file unspecified" << endl;
                return false;
            }
            if (!args.jslpRoot["FILTER"].isMember("mode")) {
                cerr << "Filter \"mode\" in jslp file unspecified" << endl;
                return false;
            }

            if (args.jslpRoot["FILTER"]["type"] == "channels") {
                filterType = FilterType::CHANNELS;
                cout << "Filtering based on channels" << endl;
            } else {
                cerr << "Filter \"mode\" unrecognized: "
                     << args.jslpRoot["FILTER"]["mode"] << endl;
                return false;
            }

            if (args.jslpRoot["FILTER"]["mode"] == "whitelist") {
                filterMode = FilterMode::WHITELIST;
                cout << "Using whitelisting filter" << endl;
            } else if (args.jslpRoot["FILTER"]["mode"] == "blacklist") {
                filterMode = FilterMode::BLACKLIST;
                cout << "Using blacklisting filter" << endl;
            } else if (args.jslpRoot["FILTER"]["mode"] == "specified") {
                filterMode = FilterMode::SPECIFIED;
                cout << "Using specified filter" << endl;
            } else {
                cerr << "Filter \"type\" unrecognized: "
                     << args.jslpRoot["FILTER"]["type"] << endl;
                return false;
            }

            auto newChannel = [&] (string channel) {
                if (filterMode == FilterMode::SPECIFIED)
                    channelMap[channel] = args.jslpRoot["FILTER"]["channels"][channel].asBool();
                else
                    channelMap[channel] = true;

                if (args.verbose)
                    cout << channel << " : "
                         << (channelMap[channel] ? "true" : "false") << endl;
            };

            if (args.jslpRoot["FILTER"]["channels"].isArray()) {
                for (auto channel : args.jslpRoot["FILTER"]["channels"])
                    newChannel(channel.asString());
            } else {
                for (auto channel : args.jslpRoot["FILTER"]["channels"].getMemberNames())
                    newChannel(channel);
            }
        }

        return true;
    }

    int run()
    {
        int err = 0;

        uint64_t firstMsgUtime = UINT64_MAX;
        uint64_t lastMsgUtime = 0;
        uint64_t lastDispatchUtime = 0;
        bool startedPub = false;

        if (startMode == StartMode::NUM_MODES) startedPub = true;

        while (!done) {
            const zcm::LogEvent* le = zcmIn->readNextEvent();
            if (!le) {
                done = true;
                continue;
            }

            uint64_t now = TimeUtil::utime();

            if (lastMsgUtime == 0)
                lastMsgUtime = le->timestamp;

            if (lastDispatchUtime == 0)
                lastDispatchUtime = now;

            if (firstMsgUtime == UINT64_MAX)
                firstMsgUtime = (uint64_t) le->timestamp;

            uint64_t localDiff = now - lastDispatchUtime;
            uint64_t logDiff = (uint64_t) le->timestamp - lastMsgUtime;
            uint64_t logDiffSpeed = logDiff / args.speed;
            uint64_t diff = logDiffSpeed > localDiff ? logDiffSpeed - localDiff
                                                     : 0;
            // TODO: this doesn't reproduce the input frequency perfectly but that is likely
            //       due to the difficulty of accurately timing events with the OS scheduler
            //       active. If it becomes an issue in the future, we could devote more time
            //       to improving the loop timing accuracy.
            //       Note that this inaccuracy does not apply if you are filting a log into
            //       a different log via a jslp file because the log times are preserved.
            //       Possible resource: http://www.tldp.org/HOWTO/IO-Port-Programming-4.html
            timespec delay;
            delay.tv_sec = (long int) diff / 1000000;
            delay.tv_nsec = (long int) (diff - (delay.tv_sec * 1000000)) * 1000;
            if (diff > 3 && startedPub) nanosleep(&delay, nullptr);

            if (!startedPub) {
                if (startMode == StartMode::CHANNEL) {
                    if (le->channel == startChan)
                        startedPub = true;
                } else if (startMode == StartMode::US_DELAY) {
                    if ((uint64_t) le->timestamp > firstMsgUtime + startDelayUs)
                        startedPub = true;
                }
            }

            auto publish = [&](){
                if (args.verbose)
                    printf("%.3f Channel %-20s size %d\n", le->timestamp / 1e6,
                           le->channel.c_str(), le->datalen);

                if (args.outfile == "")
                    zcmOut->publish(le->channel, le->data, le->datalen);
                else
                    logOut->writeEvent(le);
            };

            if (startedPub) {
                if (!filtering) {
                    publish();
                } else {
                    if (filterType == FilterType::CHANNELS) {
                        if (filterMode == FilterMode::WHITELIST) {
                            if (channelMap.count(le->channel) > 0) publish();
                        } else if (filterMode == FilterMode::BLACKLIST) {
                            if (channelMap.count(le->channel) == 0) publish();
                        } else if (filterMode == FilterMode::SPECIFIED) {
                            if (channelMap.count(le->channel) == 0) {
                                cerr << "jslp file does not specify filtering behavior "
                                     << "for channel: " << le->channel << endl;
                                done = true;
                                err = 1;
                                continue;
                            }
                            if (channelMap[le->channel]) publish();
                        } else {
                            assert(false && "Fatal error.");
                        }
                    } else {
                        assert(false && "Fatal error.");
                    }
                }
            }

            lastDispatchUtime = TimeUtil::utime();
            lastMsgUtime = le->timestamp;
        }

        return err;
    }
};

int main(int argc, char* argv[])
{
    LogPlayer lp;
    if (!lp.init(argc, argv)) return 1;

    // Register signal handlers
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGTERM, sighandler);

    int ret = lp.run();

    cout << "zcm-logplayer done" << endl;

    return ret;
}
