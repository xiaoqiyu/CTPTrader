// Copyright 2010-2014 Google
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <zlib.h>
#include <memory>
#include <string>
#include "recordio.h"

namespace recordio {
const int RecordWriter::kMagicNumber = 0x3ed7230a;

RecordWriter::RecordWriter(std::ofstream* const file)
    : file_(file), use_compression_(false) {}

bool RecordWriter::Close() {
  file_->close();
  return !file_->fail();
}

void RecordWriter::set_use_compression(bool use_compression) {
  use_compression_ = use_compression;
}

std::string RecordWriter::Compress(const char* source, size_t source_size) const {
  unsigned long dsize = source_size + (source_size * 0.1f) + 16;  // NOLINT
  std::string destination;
  destination.resize(dsize);
  // Use compress() from zlib.h.
  // const int result =
      compress(reinterpret_cast<unsigned char*>(&(destination[0])), &dsize,
               reinterpret_cast<const unsigned char*>(source), source_size);

  // if (result != Z_OK) {
  //   LOG(FATAL) << "Compress error occured! Error code: " << result;
  // }
  destination.resize(dsize);
  return std::move(destination);
}

RecordReader::RecordReader(std::ifstream* const file) : file_(file) {}

bool RecordReader::Close() { 
  file_->close();
  return !file_->fail();
}

void RecordReader::Uncompress(const char* const source, uint64_t source_size,
                              char* const output_buffer,
                              uint64_t output_size) const {
  unsigned long result_size = output_size;  // NOLINT
  // Use uncompress() from zlib.h
  // const int result =
      uncompress(reinterpret_cast<unsigned char*>(output_buffer), &result_size,
                 reinterpret_cast<const unsigned char*>(source), source_size);
  // if (result != Z_OK) {
  //   LOG(FATAL) << "Uncompress error occured! Error code: " << result;
  // }
  // CHECK_LE(result_size, static_cast<unsigned long>(output_size));  // NOLINT
}
}  // namespace recordio
