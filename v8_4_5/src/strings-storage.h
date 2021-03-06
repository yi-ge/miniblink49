// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_STRINGS_STORAGE_H_
#define V8_STRINGS_STORAGE_H_

#include "src/allocation.h"
#include "src/hashmap.h"

namespace v8 {
namespace internal {

struct OffsetRange;

// Provides a storage of strings allocated in C++ heap, to hold them
// forever, even if they disappear from JS heap or external storage.
class StringsStorage {
 public:
  explicit StringsStorage(Heap* heap);
  ~StringsStorage();

  const char* GetCopy(const char* src);
  const char* GetFormatted(const char* format, ...);
  const char* GetVFormatted(const char* format, va_list args);
  const char* GetName(Name* name);
  const char* GetName(int index);
  const char* GetFunctionName(Name* name);
  const char* GetFunctionName(const char* name);
  size_t GetUsedMemorySize() const;

 private:
  static const int kMaxNameSize = 1024;

  static bool StringsMatch(void* key1, void* key2);
  const char* AddOrDisposeString(char* str, int len);
  HashMap::Entry* GetEntry(const char* str, int len);

  uint32_t hash_seed_;
  HashMap names_;

  DISALLOW_COPY_AND_ASSIGN(StringsStorage);
};
}
}  // namespace v8::internal

#endif  // V8_STRINGS_STORAGE_H_
