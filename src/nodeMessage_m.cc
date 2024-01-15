//
// Generated file, do not edit! Created by opp_msgtool 6.0 from nodeMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "nodeMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

class bitsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    bitsDescriptor();
    virtual ~bitsDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(bitsDescriptor)

bitsDescriptor::bitsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(bits)), "")
{
    propertyNames = nullptr;
}

bitsDescriptor::~bitsDescriptor()
{
    delete[] propertyNames;
}

bool bitsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<bits *>(obj)!=nullptr;
}

const char **bitsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *bitsDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int bitsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int bitsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *bitsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int bitsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *bitsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **bitsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *bitsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int bitsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void bitsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'bits'", field);
    }
}

const char *bitsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string bitsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void bitsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'bits'", field);
    }
}

omnetpp::cValue bitsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'bits' as cValue -- field index out of range?", field);
    }
}

void bitsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'bits'", field);
    }
}

const char *bitsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr bitsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void bitsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    bits *pp = omnetpp::fromAnyPtr<bits>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'bits'", field);
    }
}

nodeMessage_Base::nodeMessage_Base(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

nodeMessage_Base::nodeMessage_Base(const nodeMessage_Base& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

nodeMessage_Base::~nodeMessage_Base()
{
}

nodeMessage_Base& nodeMessage_Base::operator=(const nodeMessage_Base& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void nodeMessage_Base::copy(const nodeMessage_Base& other)
{
    this->seqNumber = other.seqNumber;
    this->type = other.type;
    this->flag = other.flag;
    this->payload = other.payload;
    this->checksum = other.checksum;
}

void nodeMessage_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->seqNumber);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->flag);
    doParsimPacking(b,this->payload);
    doParsimPacking(b,this->checksum);
}

void nodeMessage_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->seqNumber);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->flag);
    doParsimUnpacking(b,this->payload);
    doParsimUnpacking(b,this->checksum);
}

int nodeMessage_Base::getSeqNumber() const
{
    return this->seqNumber;
}

void nodeMessage_Base::setSeqNumber(int seqNumber)
{
    this->seqNumber = seqNumber;
}

int nodeMessage_Base::getType() const
{
    return this->type;
}

void nodeMessage_Base::setType(int type)
{
    this->type = type;
}

const char * nodeMessage_Base::getFlag() const
{
    return this->flag.c_str();
}

void nodeMessage_Base::setFlag(const char * flag)
{
    this->flag = flag;
}

const char * nodeMessage_Base::getPayload() const
{
    return this->payload.c_str();
}

void nodeMessage_Base::setPayload(const char * payload)
{
    this->payload = payload;
}

const bits& nodeMessage_Base::getChecksum() const
{
    return this->checksum;
}

void nodeMessage_Base::setChecksum(const bits& checksum)
{
    this->checksum = checksum;
}

class nodeMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_seqNumber,
        FIELD_type,
        FIELD_flag,
        FIELD_payload,
        FIELD_checksum,
    };
  public:
    nodeMessageDescriptor();
    virtual ~nodeMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(nodeMessageDescriptor)

nodeMessageDescriptor::nodeMessageDescriptor() : omnetpp::cClassDescriptor("nodeMessage", "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

nodeMessageDescriptor::~nodeMessageDescriptor()
{
    delete[] propertyNames;
}

bool nodeMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<nodeMessage_Base *>(obj)!=nullptr;
}

const char **nodeMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *nodeMessageDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "customize")) return "true";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int nodeMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int nodeMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_seqNumber
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_flag
        FD_ISEDITABLE,    // FIELD_payload
        FD_ISCOMPOUND,    // FIELD_checksum
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *nodeMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "seqNumber",
        "type",
        "flag",
        "payload",
        "checksum",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int nodeMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "seqNumber") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "flag") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "payload") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "checksum") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *nodeMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_seqNumber
        "int",    // FIELD_type
        "string",    // FIELD_flag
        "string",    // FIELD_payload
        "bits",    // FIELD_checksum
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **nodeMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *nodeMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int nodeMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void nodeMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'nodeMessage_Base'", field);
    }
}

const char *nodeMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string nodeMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        case FIELD_seqNumber: return long2string(pp->getSeqNumber());
        case FIELD_type: return long2string(pp->getType());
        case FIELD_flag: return oppstring2string(pp->getFlag());
        case FIELD_payload: return oppstring2string(pp->getPayload());
        case FIELD_checksum: return pp->getChecksum().to_string();
        default: return "";
    }
}

void nodeMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        case FIELD_seqNumber: pp->setSeqNumber(string2long(value)); break;
        case FIELD_type: pp->setType(string2long(value)); break;
        case FIELD_flag: pp->setFlag((value)); break;
        case FIELD_payload: pp->setPayload((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'nodeMessage_Base'", field);
    }
}

omnetpp::cValue nodeMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        case FIELD_seqNumber: return pp->getSeqNumber();
        case FIELD_type: return pp->getType();
        case FIELD_flag: return pp->getFlag();
        case FIELD_payload: return pp->getPayload();
        case FIELD_checksum: return omnetpp::toAnyPtr(&pp->getChecksum()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'nodeMessage_Base' as cValue -- field index out of range?", field);
    }
}

void nodeMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        case FIELD_seqNumber: pp->setSeqNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_type: pp->setType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_flag: pp->setFlag(value.stringValue()); break;
        case FIELD_payload: pp->setPayload(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'nodeMessage_Base'", field);
    }
}

const char *nodeMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_checksum: return omnetpp::opp_typename(typeid(bits));
        default: return nullptr;
    };
}

omnetpp::any_ptr nodeMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        case FIELD_checksum: return omnetpp::toAnyPtr(&pp->getChecksum()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void nodeMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    nodeMessage_Base *pp = omnetpp::fromAnyPtr<nodeMessage_Base>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'nodeMessage_Base'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

