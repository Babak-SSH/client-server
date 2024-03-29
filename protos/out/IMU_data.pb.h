// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: IMU_data.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_IMU_5fdata_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_IMU_5fdata_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_IMU_5fdata_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_IMU_5fdata_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_IMU_5fdata_2eproto;
namespace IMU {
class IMU_data;
class IMU_dataDefaultTypeInternal;
extern IMU_dataDefaultTypeInternal _IMU_data_default_instance_;
}  // namespace IMU
PROTOBUF_NAMESPACE_OPEN
template<> ::IMU::IMU_data* Arena::CreateMaybeMessage<::IMU::IMU_data>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace IMU {

// ===================================================================

class IMU_data PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:IMU.IMU_data) */ {
 public:
  inline IMU_data() : IMU_data(nullptr) {};
  virtual ~IMU_data();

  IMU_data(const IMU_data& from);
  IMU_data(IMU_data&& from) noexcept
    : IMU_data() {
    *this = ::std::move(from);
  }

  inline IMU_data& operator=(const IMU_data& from) {
    CopyFrom(from);
    return *this;
  }
  inline IMU_data& operator=(IMU_data&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const IMU_data& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const IMU_data* internal_default_instance() {
    return reinterpret_cast<const IMU_data*>(
               &_IMU_data_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(IMU_data& a, IMU_data& b) {
    a.Swap(&b);
  }
  inline void Swap(IMU_data* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(IMU_data* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline IMU_data* New() const final {
    return CreateMaybeMessage<IMU_data>(nullptr);
  }

  IMU_data* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<IMU_data>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const IMU_data& from);
  void MergeFrom(const IMU_data& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(IMU_data* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "IMU.IMU_data";
  }
  protected:
  explicit IMU_data(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_IMU_5fdata_2eproto);
    return ::descriptor_table_IMU_5fdata_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRollFieldNumber = 1,
    kPitchFieldNumber = 2,
    kAccXFieldNumber = 3,
    kAccYFieldNumber = 4,
    kAccZFieldNumber = 5,
    kGyroXFieldNumber = 6,
    kGyroYFieldNumber = 7,
    kGyroZFieldNumber = 8,
  };
  // float roll = 1;
  bool has_roll() const;
  private:
  bool _internal_has_roll() const;
  public:
  void clear_roll();
  float roll() const;
  void set_roll(float value);
  private:
  float _internal_roll() const;
  void _internal_set_roll(float value);
  public:

  // float pitch = 2;
  bool has_pitch() const;
  private:
  bool _internal_has_pitch() const;
  public:
  void clear_pitch();
  float pitch() const;
  void set_pitch(float value);
  private:
  float _internal_pitch() const;
  void _internal_set_pitch(float value);
  public:

  // float acc_x = 3;
  bool has_acc_x() const;
  private:
  bool _internal_has_acc_x() const;
  public:
  void clear_acc_x();
  float acc_x() const;
  void set_acc_x(float value);
  private:
  float _internal_acc_x() const;
  void _internal_set_acc_x(float value);
  public:

  // float acc_y = 4;
  bool has_acc_y() const;
  private:
  bool _internal_has_acc_y() const;
  public:
  void clear_acc_y();
  float acc_y() const;
  void set_acc_y(float value);
  private:
  float _internal_acc_y() const;
  void _internal_set_acc_y(float value);
  public:

  // float acc_z = 5;
  bool has_acc_z() const;
  private:
  bool _internal_has_acc_z() const;
  public:
  void clear_acc_z();
  float acc_z() const;
  void set_acc_z(float value);
  private:
  float _internal_acc_z() const;
  void _internal_set_acc_z(float value);
  public:

  // float gyro_x = 6;
  bool has_gyro_x() const;
  private:
  bool _internal_has_gyro_x() const;
  public:
  void clear_gyro_x();
  float gyro_x() const;
  void set_gyro_x(float value);
  private:
  float _internal_gyro_x() const;
  void _internal_set_gyro_x(float value);
  public:

  // float gyro_y = 7;
  bool has_gyro_y() const;
  private:
  bool _internal_has_gyro_y() const;
  public:
  void clear_gyro_y();
  float gyro_y() const;
  void set_gyro_y(float value);
  private:
  float _internal_gyro_y() const;
  void _internal_set_gyro_y(float value);
  public:

  // float gyro_z = 8;
  bool has_gyro_z() const;
  private:
  bool _internal_has_gyro_z() const;
  public:
  void clear_gyro_z();
  float gyro_z() const;
  void set_gyro_z(float value);
  private:
  float _internal_gyro_z() const;
  void _internal_set_gyro_z(float value);
  public:

  // @@protoc_insertion_point(class_scope:IMU.IMU_data)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  float roll_;
  float pitch_;
  float acc_x_;
  float acc_y_;
  float acc_z_;
  float gyro_x_;
  float gyro_y_;
  float gyro_z_;
  friend struct ::TableStruct_IMU_5fdata_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// IMU_data

// float roll = 1;
inline bool IMU_data::_internal_has_roll() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool IMU_data::has_roll() const {
  return _internal_has_roll();
}
inline void IMU_data::clear_roll() {
  roll_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline float IMU_data::_internal_roll() const {
  return roll_;
}
inline float IMU_data::roll() const {
  // @@protoc_insertion_point(field_get:IMU.IMU_data.roll)
  return _internal_roll();
}
inline void IMU_data::_internal_set_roll(float value) {
  _has_bits_[0] |= 0x00000001u;
  roll_ = value;
}
inline void IMU_data::set_roll(float value) {
  _internal_set_roll(value);
  // @@protoc_insertion_point(field_set:IMU.IMU_data.roll)
}

// float pitch = 2;
inline bool IMU_data::_internal_has_pitch() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool IMU_data::has_pitch() const {
  return _internal_has_pitch();
}
inline void IMU_data::clear_pitch() {
  pitch_ = 0;
  _has_bits_[0] &= ~0x00000002u;
}
inline float IMU_data::_internal_pitch() const {
  return pitch_;
}
inline float IMU_data::pitch() const {
  // @@protoc_insertion_point(field_get:IMU.IMU_data.pitch)
  return _internal_pitch();
}
inline void IMU_data::_internal_set_pitch(float value) {
  _has_bits_[0] |= 0x00000002u;
  pitch_ = value;
}
inline void IMU_data::set_pitch(float value) {
  _internal_set_pitch(value);
  // @@protoc_insertion_point(field_set:IMU.IMU_data.pitch)
}

// float acc_x = 3;
inline bool IMU_data::_internal_has_acc_x() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool IMU_data::has_acc_x() const {
  return _internal_has_acc_x();
}
inline void IMU_data::clear_acc_x() {
  acc_x_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline float IMU_data::_internal_acc_x() const {
  return acc_x_;
}
inline float IMU_data::acc_x() const {
  // @@protoc_insertion_point(field_get:IMU.IMU_data.acc_x)
  return _internal_acc_x();
}
inline void IMU_data::_internal_set_acc_x(float value) {
  _has_bits_[0] |= 0x00000004u;
  acc_x_ = value;
}
inline void IMU_data::set_acc_x(float value) {
  _internal_set_acc_x(value);
  // @@protoc_insertion_point(field_set:IMU.IMU_data.acc_x)
}

// float acc_y = 4;
inline bool IMU_data::_internal_has_acc_y() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool IMU_data::has_acc_y() const {
  return _internal_has_acc_y();
}
inline void IMU_data::clear_acc_y() {
  acc_y_ = 0;
  _has_bits_[0] &= ~0x00000008u;
}
inline float IMU_data::_internal_acc_y() const {
  return acc_y_;
}
inline float IMU_data::acc_y() const {
  // @@protoc_insertion_point(field_get:IMU.IMU_data.acc_y)
  return _internal_acc_y();
}
inline void IMU_data::_internal_set_acc_y(float value) {
  _has_bits_[0] |= 0x00000008u;
  acc_y_ = value;
}
inline void IMU_data::set_acc_y(float value) {
  _internal_set_acc_y(value);
  // @@protoc_insertion_point(field_set:IMU.IMU_data.acc_y)
}

// float acc_z = 5;
inline bool IMU_data::_internal_has_acc_z() const {
  bool value = (_has_bits_[0] & 0x00000010u) != 0;
  return value;
}
inline bool IMU_data::has_acc_z() const {
  return _internal_has_acc_z();
}
inline void IMU_data::clear_acc_z() {
  acc_z_ = 0;
  _has_bits_[0] &= ~0x00000010u;
}
inline float IMU_data::_internal_acc_z() const {
  return acc_z_;
}
inline float IMU_data::acc_z() const {
  // @@protoc_insertion_point(field_get:IMU.IMU_data.acc_z)
  return _internal_acc_z();
}
inline void IMU_data::_internal_set_acc_z(float value) {
  _has_bits_[0] |= 0x00000010u;
  acc_z_ = value;
}
inline void IMU_data::set_acc_z(float value) {
  _internal_set_acc_z(value);
  // @@protoc_insertion_point(field_set:IMU.IMU_data.acc_z)
}

// float gyro_x = 6;
inline bool IMU_data::_internal_has_gyro_x() const {
  bool value = (_has_bits_[0] & 0x00000020u) != 0;
  return value;
}
inline bool IMU_data::has_gyro_x() const {
  return _internal_has_gyro_x();
}
inline void IMU_data::clear_gyro_x() {
  gyro_x_ = 0;
  _has_bits_[0] &= ~0x00000020u;
}
inline float IMU_data::_internal_gyro_x() const {
  return gyro_x_;
}
inline float IMU_data::gyro_x() const {
  // @@protoc_insertion_point(field_get:IMU.IMU_data.gyro_x)
  return _internal_gyro_x();
}
inline void IMU_data::_internal_set_gyro_x(float value) {
  _has_bits_[0] |= 0x00000020u;
  gyro_x_ = value;
}
inline void IMU_data::set_gyro_x(float value) {
  _internal_set_gyro_x(value);
  // @@protoc_insertion_point(field_set:IMU.IMU_data.gyro_x)
}

// float gyro_y = 7;
inline bool IMU_data::_internal_has_gyro_y() const {
  bool value = (_has_bits_[0] & 0x00000040u) != 0;
  return value;
}
inline bool IMU_data::has_gyro_y() const {
  return _internal_has_gyro_y();
}
inline void IMU_data::clear_gyro_y() {
  gyro_y_ = 0;
  _has_bits_[0] &= ~0x00000040u;
}
inline float IMU_data::_internal_gyro_y() const {
  return gyro_y_;
}
inline float IMU_data::gyro_y() const {
  // @@protoc_insertion_point(field_get:IMU.IMU_data.gyro_y)
  return _internal_gyro_y();
}
inline void IMU_data::_internal_set_gyro_y(float value) {
  _has_bits_[0] |= 0x00000040u;
  gyro_y_ = value;
}
inline void IMU_data::set_gyro_y(float value) {
  _internal_set_gyro_y(value);
  // @@protoc_insertion_point(field_set:IMU.IMU_data.gyro_y)
}

// float gyro_z = 8;
inline bool IMU_data::_internal_has_gyro_z() const {
  bool value = (_has_bits_[0] & 0x00000080u) != 0;
  return value;
}
inline bool IMU_data::has_gyro_z() const {
  return _internal_has_gyro_z();
}
inline void IMU_data::clear_gyro_z() {
  gyro_z_ = 0;
  _has_bits_[0] &= ~0x00000080u;
}
inline float IMU_data::_internal_gyro_z() const {
  return gyro_z_;
}
inline float IMU_data::gyro_z() const {
  // @@protoc_insertion_point(field_get:IMU.IMU_data.gyro_z)
  return _internal_gyro_z();
}
inline void IMU_data::_internal_set_gyro_z(float value) {
  _has_bits_[0] |= 0x00000080u;
  gyro_z_ = value;
}
inline void IMU_data::set_gyro_z(float value) {
  _internal_set_gyro_z(value);
  // @@protoc_insertion_point(field_set:IMU.IMU_data.gyro_z)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace IMU

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_IMU_5fdata_2eproto
