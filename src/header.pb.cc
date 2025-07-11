// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: header.proto

#include "header.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace fixbug {
PROTOBUF_CONSTEXPR header::header(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.servicename_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.methodname_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.args_size_)*/0u
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct headerDefaultTypeInternal {
  PROTOBUF_CONSTEXPR headerDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~headerDefaultTypeInternal() {}
  union {
    header _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 headerDefaultTypeInternal _header_default_instance_;
}  // namespace fixbug
static ::_pb::Metadata file_level_metadata_header_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_header_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_header_2eproto = nullptr;

const uint32_t TableStruct_header_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::fixbug::header, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::fixbug::header, _impl_.servicename_),
  PROTOBUF_FIELD_OFFSET(::fixbug::header, _impl_.methodname_),
  PROTOBUF_FIELD_OFFSET(::fixbug::header, _impl_.args_size_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::fixbug::header)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::fixbug::_header_default_instance_._instance,
};

const char descriptor_table_protodef_header_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014header.proto\022\006fixbug\"D\n\006header\022\023\n\013serv"
  "iceName\030\001 \001(\014\022\022\n\nmethodName\030\002 \001(\014\022\021\n\targ"
  "s_size\030\003 \001(\rb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_header_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_header_2eproto = {
    false, false, 100, descriptor_table_protodef_header_2eproto,
    "header.proto",
    &descriptor_table_header_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_header_2eproto::offsets,
    file_level_metadata_header_2eproto, file_level_enum_descriptors_header_2eproto,
    file_level_service_descriptors_header_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_header_2eproto_getter() {
  return &descriptor_table_header_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_header_2eproto(&descriptor_table_header_2eproto);
namespace fixbug {

// ===================================================================

class header::_Internal {
 public:
};

header::header(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:fixbug.header)
}
header::header(const header& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  header* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.servicename_){}
    , decltype(_impl_.methodname_){}
    , decltype(_impl_.args_size_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.servicename_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.servicename_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_servicename().empty()) {
    _this->_impl_.servicename_.Set(from._internal_servicename(), 
      _this->GetArenaForAllocation());
  }
  _impl_.methodname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.methodname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_methodname().empty()) {
    _this->_impl_.methodname_.Set(from._internal_methodname(), 
      _this->GetArenaForAllocation());
  }
  _this->_impl_.args_size_ = from._impl_.args_size_;
  // @@protoc_insertion_point(copy_constructor:fixbug.header)
}

inline void header::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.servicename_){}
    , decltype(_impl_.methodname_){}
    , decltype(_impl_.args_size_){0u}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.servicename_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.servicename_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.methodname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.methodname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

header::~header() {
  // @@protoc_insertion_point(destructor:fixbug.header)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void header::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.servicename_.Destroy();
  _impl_.methodname_.Destroy();
}

void header::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void header::Clear() {
// @@protoc_insertion_point(message_clear_start:fixbug.header)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.servicename_.ClearToEmpty();
  _impl_.methodname_.ClearToEmpty();
  _impl_.args_size_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* header::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bytes serviceName = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_servicename();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bytes methodName = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_methodname();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 args_size = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _impl_.args_size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* header::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:fixbug.header)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes serviceName = 1;
  if (!this->_internal_servicename().empty()) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_servicename(), target);
  }

  // bytes methodName = 2;
  if (!this->_internal_methodname().empty()) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_methodname(), target);
  }

  // uint32 args_size = 3;
  if (this->_internal_args_size() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(3, this->_internal_args_size(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:fixbug.header)
  return target;
}

size_t header::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:fixbug.header)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes serviceName = 1;
  if (!this->_internal_servicename().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_servicename());
  }

  // bytes methodName = 2;
  if (!this->_internal_methodname().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_methodname());
  }

  // uint32 args_size = 3;
  if (this->_internal_args_size() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_args_size());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData header::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    header::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*header::GetClassData() const { return &_class_data_; }


void header::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<header*>(&to_msg);
  auto& from = static_cast<const header&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:fixbug.header)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_servicename().empty()) {
    _this->_internal_set_servicename(from._internal_servicename());
  }
  if (!from._internal_methodname().empty()) {
    _this->_internal_set_methodname(from._internal_methodname());
  }
  if (from._internal_args_size() != 0) {
    _this->_internal_set_args_size(from._internal_args_size());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void header::CopyFrom(const header& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:fixbug.header)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool header::IsInitialized() const {
  return true;
}

void header::InternalSwap(header* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.servicename_, lhs_arena,
      &other->_impl_.servicename_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.methodname_, lhs_arena,
      &other->_impl_.methodname_, rhs_arena
  );
  swap(_impl_.args_size_, other->_impl_.args_size_);
}

::PROTOBUF_NAMESPACE_ID::Metadata header::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_header_2eproto_getter, &descriptor_table_header_2eproto_once,
      file_level_metadata_header_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace fixbug
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::fixbug::header*
Arena::CreateMaybeMessage< ::fixbug::header >(Arena* arena) {
  return Arena::CreateMessageInternal< ::fixbug::header >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
