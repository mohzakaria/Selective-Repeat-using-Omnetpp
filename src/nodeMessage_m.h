//
// Generated file, do not edit! Created by opp_msgtool 6.0 from nodeMessage.msg.
//

#ifndef __NODEMESSAGE_M_H
#define __NODEMESSAGE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class nodeMessage;
// cplusplus {{
	#include<bitset>
	typedef std::bitset<8> bits;	
	
// }}

/**
 * Class generated from <tt>nodeMessage.msg:22</tt> by opp_msgtool.
 * <pre>
 * // TODO generated message class
 * //
 * packet nodeMessage
 * {
 *     \@customize(true);  // see the generated C++ header for more info
 *     int seqNumber;
 *     int type;
 *     string flag;
 *     string payload;
 *     bits checksum;
 * 
 * }
 * </pre>
 *
 * nodeMessage_Base is only useful if it gets subclassed, and nodeMessage is derived from it.
 * The minimum code to be written for nodeMessage is the following:
 *
 * <pre>
 * class nodeMessage : public nodeMessage_Base
 * {
 *   private:
 *     void copy(const nodeMessage& other) { ... }

 *   public:
 *     nodeMessage(const char *name=nullptr, short kind=0) : nodeMessage_Base(name,kind) {}
 *     nodeMessage(const nodeMessage& other) : nodeMessage_Base(other) {copy(other);}
 *     nodeMessage& operator=(const nodeMessage& other) {if (this==&other) return *this; nodeMessage_Base::operator=(other); copy(other); return *this;}
 *     virtual nodeMessage *dup() const override {return new nodeMessage(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from nodeMessage_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(nodeMessage)
 * </pre>
 */
class nodeMessage_Base : public ::omnetpp::cPacket
{
  protected:
    int seqNumber = 0;
    int type = 0;
    omnetpp::opp_string flag;
    omnetpp::opp_string payload;
    bits checksum;

  private:
    void copy(const nodeMessage_Base& other);

  protected:
    bool operator==(const nodeMessage_Base&) = delete;
    // make constructors protected to avoid instantiation

    nodeMessage_Base(const nodeMessage_Base& other);
    // make assignment operator protected to force the user override it
    nodeMessage_Base& operator=(const nodeMessage_Base& other);

  public:
    nodeMessage_Base(const char *name=nullptr, short kind=0);
    virtual ~nodeMessage_Base();
    virtual nodeMessage_Base *dup() const override {return new nodeMessage_Base(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getSeqNumber() const;
    virtual void setSeqNumber(int seqNumber);

    virtual int getType() const;
    virtual void setType(int type);

    virtual const char * getFlag() const;
    virtual void setFlag(const char * flag);

    virtual const char * getPayload() const;
    virtual void setPayload(const char * payload);

    virtual const bits& getChecksum() const;
    virtual bits& getChecksumForUpdate() { return const_cast<bits&>(const_cast<nodeMessage_Base*>(this)->getChecksum());}
    virtual void setChecksum(const bits& checksum);
};


namespace omnetpp {

inline any_ptr toAnyPtr(const bits *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline bits *fromAnyPtr(any_ptr ptr) { return ptr.get<bits>(); }
template<> inline nodeMessage_Base *fromAnyPtr(any_ptr ptr) { return check_and_cast<nodeMessage_Base*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __NODEMESSAGE_M_H

