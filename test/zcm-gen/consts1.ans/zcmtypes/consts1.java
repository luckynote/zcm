/* ZCM type definition class file
 * This file was automatically generated by zcm-gen
 * DO NOT MODIFY BY HAND!!!!
 */

package zcmtypes;
 
import java.io.*;
import java.util.*;
import zcm.zcm.*;
 
public final class consts1 implements zcm.zcm.ZCMEncodable
{
 
    public consts1()
    {
    }
 
    public static final long ZCM_FINGERPRINT;
    public static final long ZCM_FINGERPRINT_BASE = 0x0000000012345678L;
 
    public static final byte k8 = (byte) 1;
    public static final short k16 = (short) 2;
    public static final int i32 = 3;
    public static final long i64 = 4L;
    public static final float f = 5.0f;
    public static final double d = 6.0;

    static {
        ZCM_FINGERPRINT = _hashRecursive(new ArrayList<Class<?>>());
    }
 
    public static long _hashRecursive(ArrayList<Class<?>> classes)
    {
        if (classes.contains(zcmtypes.consts1.class))
            return 0L;
 
        classes.add(zcmtypes.consts1.class);
        long hash = ZCM_FINGERPRINT_BASE
            ;
        classes.remove(classes.size() - 1);
        return (hash<<1) + ((hash>>63)&1);
    }
 
    public void encode(DataOutput outs) throws IOException
    {
        outs.writeLong(ZCM_FINGERPRINT);
        _encodeRecursive(outs);
    }
 
    public void _encodeRecursive(DataOutput outs) throws IOException
    {
    }
 
    public consts1(byte[] data) throws IOException
    {
        this(new ZCMDataInputStream(data));
    }
 
    public consts1(DataInput ins) throws IOException
    {
        if (ins.readLong() != ZCM_FINGERPRINT)
            throw new IOException("ZCM Decode error: bad fingerprint");
 
        _decodeRecursive(ins);
    }
 
    public static zcmtypes.consts1 _decodeRecursiveFactory(DataInput ins) throws IOException
    {
        zcmtypes.consts1 o = new zcmtypes.consts1();
        o._decodeRecursive(ins);
        return o;
    }
 
    public void _decodeRecursive(DataInput ins) throws IOException
    {
    }
 
    public zcmtypes.consts1 copy()
    {
        zcmtypes.consts1 outobj = new zcmtypes.consts1();
        return outobj;
    }
 
}

