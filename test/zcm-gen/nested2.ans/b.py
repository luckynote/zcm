/* ZCM type definition class file
 * This file was automatically generated by zcm-gen
 * DO NOT MODIFY BY HAND!!!!
 */

package zcmtypes;
 
import java.io.*;
import java.util.*;
import zcm.zcm.*;
 
public final class b implements zcm.zcm.ZCMEncodable
{
    public int val2;
    public zcmtypes.a a_;
 
    public b()
    {
    }
 
    public static final long ZCM_FINGERPRINT;
    public static final long ZCM_FINGERPRINT_BASE = 0xf53820e02f1e593fL;
 
    static {
        ZCM_FINGERPRINT = _hashRecursive(new ArrayList<Class<?>>());
    }
 
    public static long _hashRecursive(ArrayList<Class<?>> classes)
    {
        if (classes.contains(zcmtypes.b.class))
            return 0L;
 
        classes.add(zcmtypes.b.class);
        long hash = ZCM_FINGERPRINT_BASE
             + zcmtypes.a._hashRecursive(classes)
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
        outs.writeInt(this.val2); 
 
        this.a_._encodeRecursive(outs); 
 
    }
 
    public b(byte[] data) throws IOException
    {
        this(new ZCMDataInputStream(data));
    }
 
    public b(DataInput ins) throws IOException
    {
        if (ins.readLong() != ZCM_FINGERPRINT)
            throw new IOException("ZCM Decode error: bad fingerprint");
 
        _decodeRecursive(ins);
    }
 
    public static zcmtypes.b _decodeRecursiveFactory(DataInput ins) throws IOException
    {
        zcmtypes.b o = new zcmtypes.b();
        o._decodeRecursive(ins);
        return o;
    }
 
    public void _decodeRecursive(DataInput ins) throws IOException
    {
        this.val2 = ins.readInt();
 
        this.a_ = zcmtypes.a._decodeRecursiveFactory(ins);
 
    }
 
    public zcmtypes.b copy()
    {
        zcmtypes.b outobj = new zcmtypes.b();
        outobj.val2 = this.val2;
 
        outobj.a_ = this.a_.copy();
 
        return outobj;
    }
 
}

