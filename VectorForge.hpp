//VectorForge 0.3.0 advanced vector math library
//Copyright (c) 2026 StellarWorks/Xada Engine
//
//SPDX-License-Identifier: GPL-3.0-only
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of version 3 of the GNU General Public License as
//published by the Free Software Foundation.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program. If not, see <https://www.gnu.org/licenses/>.
//
//COMMERCIAL LICENSING
//This software is distributed under the GNU General Public License
//version 3. The copyright holder reserves the right to license it
//under separate commercial terms; no such licence is granted except
//by written agreement with the copyright holder.

#pragma once
#include <immintrin.h>
#include <cstdint>
#include <cstddef>
#include <cmath>

#ifndef __AVX2__
#error "VectorForge requires AVX2 and FMA3. Set /arch:AVX2 (MSVC) or -mavx2 -mfma (GCC/Clang)."
#endif

#if !defined(_MSC_VER) && !defined(__FMA__)
#error "VectorForge requires FMA3. Add -mfma (GCC/Clang)."
#endif

#if defined(__has_include)
#  if __has_include(<DirectXMath.h>)
#    include <DirectXMath.h>
#    define XMATH 1
#  endif
#endif
namespace VFX {
    //Nothing in this library is comparable: every type deletes its
    //comparison operators, because none of these answer a yes/no question
    //about a whole vector.

    //=====================================================================
    // STORAGE VECTORS
    // When performing vector operations with a scalar input, the scalar is
    // always applied to the vector, NEVER the other way around. This is
    // enforced by the language: the scalar operators are members, so the
    // vector must be the left operand.
    // 
    // <= is the splat operator, which will fill a vector with the given
    // value. On the register types it broadcasts to every lane.
    //  
    // The alias structs are anonymous, which is a compiler extension
    // rather than ISO C++. The standard has no grammar for a struct
    // declared inside a union with no member name. MSVC, GCC and Clang
    // all accept it; only -pedantic-errors rejects it. Naming the members would
    // be conforming, but it costs being able to address member aliases directly.
    // 
    // Reading through a different alias than the one written is well
    // defined here: all three are standard-layout structs with the same
    // member sequence, so the common initial sequence rule covers every
    // member.
    //=====================================================================
    #pragma region Storage_Vectors
    //Float2 type
    struct float2 {
        union {
            struct { float x, y; };
            struct { float u, v; };
            struct { float Width, Height; };
        };

        //Vector-vector
        float2 operator+(const float2 Second) const {
            float2 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            return Result;
        }
        float2 operator-(const float2 Second) const {
            float2 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            return Result;
        }
        float2 operator*(const float2 Second) const {
            float2 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            return Result;
        }
        float2 operator/(const float2 Second) const {
            float2 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            return Result;
        }

        //Vector-scalar
        float2 operator+(const float Second) const {
            float2 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            return Result;
        }
        float2 operator-(const float Second) const {
            float2 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            return Result;
        }
        float2 operator*(const float Second) const {
            float2 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            return Result;
        }
        float2 operator/(const float Second) const {
            float2 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            return Result;
        }

        //Splat
        float2& operator<=(const float Second) {
            x = Second;
            y = Second;
            return *this;
        }

        bool operator==(const float2&) const = delete;
        bool operator!=(const float2&) const = delete;
        bool operator<(const float2&) const = delete;
        bool operator>(const float2&) const = delete;
        bool operator>=(const float2&) const = delete;
        bool operator<=>(const float2&) const = delete;

        #ifdef XMATH
        float2(const DirectX::XMFLOAT2& Source) { x = Source.x; y = Source.y; }
        operator DirectX::XMFLOAT2() const { return DirectX::XMFLOAT2(x, y); }
        #endif

        float2(float X, float Y) { x = X; y = Y; }
        float2() { x = 0.f; y = 0.f; }
    };
    //Float3 type
    struct float3 {
        union {
            struct { float x, y, z; };
            struct { float r, g, b; };
            struct { float Width, Height, Depth; };
        };

        //Vector-vector
        float3 operator+(const float3 Second) const {
            float3 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            Result.z = z + Second.z;
            return Result;
        }
        float3 operator-(const float3 Second) const {
            float3 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            Result.z = z - Second.z;
            return Result;
        }
        float3 operator*(const float3 Second) const {
            float3 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            Result.z = z * Second.z;
            return Result;
        }
        float3 operator/(const float3 Second) const {
            float3 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            Result.z = z / Second.z;
            return Result;
        }

        //Vector-scalar
        float3 operator+(const float Second) const {
            float3 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            Result.z = z + Second;
            return Result;
        }
        float3 operator-(const float Second) const {
            float3 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            Result.z = z - Second;
            return Result;
        }
        float3 operator*(const float Second) const {
            float3 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            Result.z = z * Second;
            return Result;
        }
        float3 operator/(const float Second) const {
            float3 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            Result.z = z / Second;
            return Result;
        }

        //Splat
        float3& operator<=(const float Second) {
            x = Second;
            y = Second;
            z = Second;
            return *this;
        }

        bool operator==(const float3&) const = delete;
        bool operator!=(const float3&) const = delete;
        bool operator<(const float3&) const = delete;
        bool operator>(const float3&) const = delete;
        bool operator>=(const float3&) const = delete;
        bool operator<=>(const float3&) const = delete;

        #ifdef XMATH
        float3(const DirectX::XMFLOAT3& Source) { x = Source.x; y = Source.y; z = Source.z; }
        operator DirectX::XMFLOAT3() const { return DirectX::XMFLOAT3(x, y, z); }
        #endif

        float3(float X, float Y, float Z) { x = X; y = Y; z = Z; }
        float3() { x = 0.f; y = 0.f; z = 0.f; }
    };
    //Float4 type
    struct alignas(16) float4 {
        union {
            struct { float x, y, z, w; };
            struct { float r, g, b, a; };
        };

        //Vector-vector
        float4 operator+(const float4 Second) const {
            float4 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            Result.z = z + Second.z;
            Result.w = w + Second.w;
            return Result;
        }
        float4 operator-(const float4 Second) const {
            float4 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            Result.z = z - Second.z;
            Result.w = w - Second.w;
            return Result;
        }
        float4 operator*(const float4 Second) const {
            float4 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            Result.z = z * Second.z;
            Result.w = w * Second.w;
            return Result;
        }
        float4 operator/(const float4 Second) const {
            float4 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            Result.z = z / Second.z;
            Result.w = w / Second.w;
            return Result;
        }

        //Vector-scalar
        float4 operator+(const float Second) const {
            float4 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            Result.z = z + Second;
            Result.w = w + Second;
            return Result;
        }
        float4 operator-(const float Second) const {
            float4 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            Result.z = z - Second;
            Result.w = w - Second;
            return Result;
        }
        float4 operator*(const float Second) const {
            float4 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            Result.z = z * Second;
            Result.w = w * Second;
            return Result;
        }
        float4 operator/(const float Second) const {
            float4 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            Result.z = z / Second;
            Result.w = w / Second;
            return Result;
        }

        //Splat
        float4& operator<=(const float Second) {
            x = Second;
            y = Second;
            z = Second;
            w = Second;
            return *this;
        }

        bool operator==(const float4&) const = delete;
        bool operator!=(const float4&) const = delete;
        bool operator<(const float4&) const = delete;
        bool operator>(const float4&) const = delete;
        bool operator>=(const float4&) const = delete;
        bool operator<=>(const float4&) const = delete;

        #ifdef XMATH
        float4(const DirectX::XMFLOAT4& Source) { x = Source.x; y = Source.y; z = Source.z; w = Source.w; }
        operator DirectX::XMFLOAT4() const { return DirectX::XMFLOAT4(x, y, z, w); }
        #endif

        float4(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; }
        float4() { x = 0.f; y = 0.f; z = 0.f; w = 0.f; }
    };
    //Float8 type
    struct alignas(32) float8 {
        float Data[8] = { 0.0f };

        //Vector-vector
        float8 operator+(const float8 Second) const {
            float8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] + Second.Data[Index];
            }
            return Result;
        }
        float8 operator-(const float8 Second) const {
            float8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] - Second.Data[Index];
            }
            return Result;
        }
        float8 operator*(const float8 Second) const {
            float8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] * Second.Data[Index];
            }
            return Result;
        }
        float8 operator/(const float8 Second) const {
            float8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] / Second.Data[Index];
            }
            return Result;
        }

        //Vector-scalar
        float8 operator+(const float Second) const {
            float8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] + Second;
            }
            return Result;
        }
        float8 operator-(const float Second) const {
            float8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] - Second;
            }
            return Result;
        }
        float8 operator*(const float Second) const {
            float8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] * Second;
            }
            return Result;
        }
        float8 operator/(const float Second) const {
            float8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] / Second;
            }
            return Result;
        }

        //Splat
        float8& operator<=(const float Second) {
            for (size_t Index = 0; Index < 8; Index++) {
                Data[Index] = Second;
            }
            return *this;
        }

        bool operator==(const float8&) const = delete;
        bool operator!=(const float8&) const = delete;
        bool operator<(const float8&) const = delete;
        bool operator>(const float8&) const = delete;
        bool operator>=(const float8&) const = delete;
        bool operator<=>(const float8&) const = delete;
    };

    //Double2 type
    struct double2 {
        union {
            struct { double x, y; };
            struct { double u, v; };
            struct { double Width, Height; };
        };

        //Vector-vector
        double2 operator+(const double2 Second) const {
            double2 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            return Result;
        }
        double2 operator-(const double2 Second) const {
            double2 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            return Result;
        }
        double2 operator*(const double2 Second) const {
            double2 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            return Result;
        }
        double2 operator/(const double2 Second) const {
            double2 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            return Result;
        }

        //Vector-scalar
        double2 operator+(const double Second) const {
            double2 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            return Result;
        }
        double2 operator-(const double Second) const {
            double2 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            return Result;
        }
        double2 operator*(const double Second) const {
            double2 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            return Result;
        }
        double2 operator/(const double Second) const {
            double2 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            return Result;
        }

        //Splat
        double2& operator<=(const double Second) {
            x = Second;
            y = Second;
            return *this;
        }

        bool operator==(const double2&) const = delete;
        bool operator!=(const double2&) const = delete;
        bool operator<(const double2&) const = delete;
        bool operator>(const double2&) const = delete;
        bool operator>=(const double2&) const = delete;
        bool operator<=>(const double2&) const = delete;

        double2(double X, double Y) { x = X; y = Y; }
        double2() { x = 0.; y = 0.; }
    };
    //Double3 type
    struct double3 {
        union {
            struct { double x, y, z; };
            struct { double r, g, b; };
            struct { double Width, Height, Depth; };
        };

        //Vector-vector
        double3 operator+(const double3 Second) const {
            double3 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            Result.z = z + Second.z;
            return Result;
        }
        double3 operator-(const double3 Second) const {
            double3 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            Result.z = z - Second.z;
            return Result;
        }
        double3 operator*(const double3 Second) const {
            double3 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            Result.z = z * Second.z;
            return Result;
        }
        double3 operator/(const double3 Second) const {
            double3 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            Result.z = z / Second.z;
            return Result;
        }

        //Vector-scalar
        double3 operator+(const double Second) const {
            double3 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            Result.z = z + Second;
            return Result;
        }
        double3 operator-(const double Second) const {
            double3 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            Result.z = z - Second;
            return Result;
        }
        double3 operator*(const double Second) const {
            double3 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            Result.z = z * Second;
            return Result;
        }
        double3 operator/(const double Second) const {
            double3 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            Result.z = z / Second;
            return Result;
        }

        //Splat
        double3& operator<=(const double Second) {
            x = Second;
            y = Second;
            z = Second;
            return *this;
        }

        bool operator==(const double3&) const = delete;
        bool operator!=(const double3&) const = delete;
        bool operator<(const double3&) const = delete;
        bool operator>(const double3&) const = delete;
        bool operator>=(const double3&) const = delete;
        bool operator<=>(const double3&) const = delete;

        double3(double X, double Y, double Z) { x = X; y = Y; z = Z; }
        double3() { x = 0.; y = 0.; z = 0.; }
    };
    //Double4 type
    struct alignas(32) double4 {
        union {
            struct { double x, y, z, w; };
            struct { double r, g, b, a; };
        };

        //Vector-vector
        double4 operator+(const double4 Second) const {
            double4 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            Result.z = z + Second.z;
            Result.w = w + Second.w;
            return Result;
        }
        double4 operator-(const double4 Second) const {
            double4 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            Result.z = z - Second.z;
            Result.w = w - Second.w;
            return Result;
        }
        double4 operator*(const double4 Second) const {
            double4 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            Result.z = z * Second.z;
            Result.w = w * Second.w;
            return Result;
        }
        double4 operator/(const double4 Second) const {
            double4 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            Result.z = z / Second.z;
            Result.w = w / Second.w;
            return Result;
        }

        //Vector-scalar
        double4 operator+(const double Second) const {
            double4 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            Result.z = z + Second;
            Result.w = w + Second;
            return Result;
        }
        double4 operator-(const double Second) const {
            double4 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            Result.z = z - Second;
            Result.w = w - Second;
            return Result;
        }
        double4 operator*(const double Second) const {
            double4 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            Result.z = z * Second;
            Result.w = w * Second;
            return Result;
        }
        double4 operator/(const double Second) const {
            double4 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            Result.z = z / Second;
            Result.w = w / Second;
            return Result;
        }

        //Splat
        double4& operator<=(const double Second) {
            x = Second;
            y = Second;
            z = Second;
            w = Second;
            return *this;
        }

        bool operator==(const double4&) const = delete;
        bool operator!=(const double4&) const = delete;
        bool operator<(const double4&) const = delete;
        bool operator>(const double4&) const = delete;
        bool operator>=(const double4&) const = delete;
        bool operator<=>(const double4&) const = delete;

        double4(double X, double Y, double Z, double W) { x = X; y = Y; z = Z; w = W; }
        double4() { x = 0.; y = 0.; z = 0.; w = 0.; }
    };

    //Int2 type
    struct int2 {
        union {
            struct { int64_t x, y; };
            struct { int64_t u, v; };
            struct { int64_t Width, Height; };
        };

        //Vector-vector
        int2 operator+(const int2 Second) const {
            int2 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            return Result;
        }
        int2 operator-(const int2 Second) const {
            int2 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            return Result;
        }
        int2 operator*(const int2 Second) const {
            int2 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            return Result;
        }
        int2 operator/(const int2 Second) const {
            int2 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            return Result;
        }

        //Vector-scalar
        int2 operator+(const int64_t Second) const {
            int2 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            return Result;
        }
        int2 operator-(const int64_t Second) const {
            int2 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            return Result;
        }
        int2 operator*(const int64_t Second) const {
            int2 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            return Result;
        }
        int2 operator/(const int64_t Second) const {
            int2 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            return Result;
        }

        //Splat
        int2& operator<=(const int64_t Second) {
            x = Second;
            y = Second;
            return *this;
        }

        bool operator==(const int2&) const = delete;
        bool operator!=(const int2&) const = delete;
        bool operator<(const int2&) const = delete;
        bool operator>(const int2&) const = delete;
        bool operator>=(const int2&) const = delete;
        bool operator<=>(const int2&) const = delete;

        int2(int64_t X, int64_t Y) { x = X; y = Y; }
        int2() { x = 0; y = 0; }
    };
    //Int3 type
    struct int3 {
        union {
            struct { int64_t x, y, z; };
            struct { int64_t r, g, b; };
            struct { int64_t Width, Height, Depth; };
        };

        //Vector-vector
        int3 operator+(const int3 Second) const {
            int3 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            Result.z = z + Second.z;
            return Result;
        }
        int3 operator-(const int3 Second) const {
            int3 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            Result.z = z - Second.z;
            return Result;
        }
        int3 operator*(const int3 Second) const {
            int3 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            Result.z = z * Second.z;
            return Result;
        }
        int3 operator/(const int3 Second) const {
            int3 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            Result.z = z / Second.z;
            return Result;
        }

        //Vector-scalar
        int3 operator+(const int64_t Second) const {
            int3 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            Result.z = z + Second;
            return Result;
        }
        int3 operator-(const int64_t Second) const {
            int3 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            Result.z = z - Second;
            return Result;
        }
        int3 operator*(const int64_t Second) const {
            int3 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            Result.z = z * Second;
            return Result;
        }
        int3 operator/(const int64_t Second) const {
            int3 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            Result.z = z / Second;
            return Result;
        }

        //Splat
        int3& operator<=(const int64_t Second) {
            x = Second;
            y = Second;
            z = Second;
            return *this;
        }

        bool operator==(const int3&) const = delete;
        bool operator!=(const int3&) const = delete;
        bool operator<(const int3&) const = delete;
        bool operator>(const int3&) const = delete;
        bool operator>=(const int3&) const = delete;
        bool operator<=>(const int3&) const = delete;

        int3(int64_t X, int64_t Y, int64_t Z) { x = X; y = Y; z = Z; }
        int3() { x = 0; y = 0; z = 0; }
    };
    //Int4 type
    struct alignas(32) int4 {
        union {
            struct { int64_t x, y, z, w; };
            struct { int64_t r, g, b, a; };
        };

        //Vector-vector
        int4 operator+(const int4 Second) const {
            int4 Result;
            Result.x = x + Second.x;
            Result.y = y + Second.y;
            Result.z = z + Second.z;
            Result.w = w + Second.w;
            return Result;
        }
        int4 operator-(const int4 Second) const {
            int4 Result;
            Result.x = x - Second.x;
            Result.y = y - Second.y;
            Result.z = z - Second.z;
            Result.w = w - Second.w;
            return Result;
        }
        int4 operator*(const int4 Second) const {
            int4 Result;
            Result.x = x * Second.x;
            Result.y = y * Second.y;
            Result.z = z * Second.z;
            Result.w = w * Second.w;
            return Result;
        }
        int4 operator/(const int4 Second) const {
            int4 Result;
            Result.x = x / Second.x;
            Result.y = y / Second.y;
            Result.z = z / Second.z;
            Result.w = w / Second.w;
            return Result;
        }

        //Vector-scalar
        int4 operator+(const int64_t Second) const {
            int4 Result;
            Result.x = x + Second;
            Result.y = y + Second;
            Result.z = z + Second;
            Result.w = w + Second;
            return Result;
        }
        int4 operator-(const int64_t Second) const {
            int4 Result;
            Result.x = x - Second;
            Result.y = y - Second;
            Result.z = z - Second;
            Result.w = w - Second;
            return Result;
        }
        int4 operator*(const int64_t Second) const {
            int4 Result;
            Result.x = x * Second;
            Result.y = y * Second;
            Result.z = z * Second;
            Result.w = w * Second;
            return Result;
        }
        int4 operator/(const int64_t Second) const {
            int4 Result;
            Result.x = x / Second;
            Result.y = y / Second;
            Result.z = z / Second;
            Result.w = w / Second;
            return Result;
        }

        //Splat
        int4& operator<=(const int64_t Second) {
            x = Second;
            y = Second;
            z = Second;
            w = Second;
            return *this;
        }

        bool operator==(const int4&) const = delete;
        bool operator!=(const int4&) const = delete;
        bool operator<(const int4&) const = delete;
        bool operator>(const int4&) const = delete;
        bool operator>=(const int4&) const = delete;
        bool operator<=>(const int4&) const = delete;

        int4(int64_t X, int64_t Y, int64_t Z, int64_t W) { x = X; y = Y; z = Z; w = W; }
        int4() { x = 0; y = 0; z = 0; w = 0; }
    };
    //Int8 type
    struct alignas(32) int8 {
        int32_t Data[8] = { 0 };

        //Vector-vector
        int8 operator+(const int8 Second) const {
            int8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] + Second.Data[Index];
            }
            return Result;
        }
        int8 operator-(const int8 Second) const {
            int8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] - Second.Data[Index];
            }
            return Result;
        }
        int8 operator*(const int8 Second) const {
            int8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] * Second.Data[Index];
            }
            return Result;
        }
        int8 operator/(const int8 Second) const {
            int8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] / Second.Data[Index];
            }
            return Result;
        }

        //Vector-scalar
        int8 operator+(const int32_t Second) const {
            int8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] + Second;
            }
            return Result;
        }
        int8 operator-(const int32_t Second) const {
            int8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] - Second;
            }
            return Result;
        }
        int8 operator*(const int32_t Second) const {
            int8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] * Second;
            }
            return Result;
        }
        int8 operator/(const int32_t Second) const {
            int8 Result;
            for (size_t Index = 0; Index < 8; Index++) {
                Result.Data[Index] = Data[Index] / Second;
            }
            return Result;
        }

        //Splat
        int8& operator<=(const int32_t Second) {
            for (size_t Index = 0; Index < 8; Index++) {
                Data[Index] = Second;
            }
            return *this;
        }

        bool operator==(const int8&) const = delete;
        bool operator!=(const int8&) const = delete;
        bool operator<(const int8&) const = delete;
        bool operator>(const int8&) const = delete;
        bool operator>=(const int8&) const = delete;
        bool operator<=>(const int8&) const = delete;
    };
    //Int16 type
    struct alignas(32) int16 {
        int16_t Data[16] = { 0 };

        //Vector-vector
        int16 operator+(const int16 Second) const {
            int16 Result = { 0 };
            for (size_t Index = 0; Index < 16; Index++) {
                Result.Data[Index] = Data[Index] + Second.Data[Index];
            }
            return Result;
        }
        int16 operator-(const int16 Second) const {
            int16 Result = { 0 };
            for (size_t Index = 0; Index < 16; Index++) {
                Result.Data[Index] = Data[Index] - Second.Data[Index];
            }
            return Result;
        }
        int16 operator*(const int16 Second) const {
            int16 Result = { 0 };
            for (size_t Index = 0; Index < 16; Index++) {
                Result.Data[Index] = Data[Index] * Second.Data[Index];
            }
            return Result;
        }
        int16 operator/(const int16 Second) const {
            int16 Result = { 0 };
            for (size_t Index = 0; Index < 16; Index++) {
                Result.Data[Index] = Data[Index] / Second.Data[Index];
            }
            return Result;
        }

        //Vector-scalar
        int16 operator+(const int16_t Second) const {
            int16 Result = { 0 };
            for (size_t Index = 0; Index < 16; Index++) {
                Result.Data[Index] = Data[Index] + Second;
            }
            return Result;
        }
        int16 operator-(const int16_t Second) const {
            int16 Result = { 0 };
            for (size_t Index = 0; Index < 16; Index++) {
                Result.Data[Index] = Data[Index] - Second;
            }
            return Result;
        }
        int16 operator*(const int16_t Second) const {
            int16 Result = { 0 };
            for (size_t Index = 0; Index < 16; Index++) {
                Result.Data[Index] = Data[Index] * Second;
            }
            return Result;
        }
        int16 operator/(const int16_t Second) const {
            int16 Result = { 0 };
            for (size_t Index = 0; Index < 16; Index++) {
                Result.Data[Index] = Data[Index] / Second;
            }
            return Result;
        }

        //Splat
        int16& operator<=(const int16_t Second) {
            for (size_t Index = 0; Index < 16; Index++) {
                Data[Index] = Second;
            }
            return *this;
        }

        bool operator==(const int16&) const = delete;
        bool operator!=(const int16&) const = delete;
        bool operator<(const int16&) const = delete;
        bool operator>(const int16&) const = delete;
        bool operator>=(const int16&) const = delete;
        bool operator<=>(const int16&) const = delete;
    };
    //Int32 type
    struct alignas(32) int32 {
        int8_t Data[32] = { 0 };

        //Vector-vector
        int32 operator+(const int32 Second) const {
            int32 Result = { 0 };
            for (size_t Index = 0; Index < 32; Index++) {
                Result.Data[Index] = Data[Index] + Second.Data[Index];
            }
            return Result;
        }
        int32 operator-(const int32 Second) const {
            int32 Result = { 0 };
            for (size_t Index = 0; Index < 32; Index++) {
                Result.Data[Index] = Data[Index] - Second.Data[Index];
            }
            return Result;
        }
        int32 operator*(const int32 Second) const {
            int32 Result = { 0 };
            for (size_t Index = 0; Index < 32; Index++) {
                Result.Data[Index] = Data[Index] * Second.Data[Index];
            }
            return Result;
        }
        int32 operator/(const int32 Second) const {
            int32 Result = { 0 };
            for (size_t Index = 0; Index < 32; Index++) {
                Result.Data[Index] = Data[Index] / Second.Data[Index];
            }
            return Result;
        }

        //Vector-scalar
        int32 operator+(const int8_t Second) const {
            int32 Result = { 0 };
            for (size_t Index = 0; Index < 32; Index++) {
                Result.Data[Index] = Data[Index] + Second;
            }
            return Result;
        }
        int32 operator-(const int8_t Second) const {
            int32 Result = { 0 };
            for (size_t Index = 0; Index < 32; Index++) {
                Result.Data[Index] = Data[Index] - Second;
            }
            return Result;
        }
        int32 operator*(const int8_t Second) const {
            int32 Result = { 0 };
            for (size_t Index = 0; Index < 32; Index++) {
                Result.Data[Index] = Data[Index] * Second;
            }
            return Result;
        }
        int32 operator/(const int8_t Second) const {
            int32 Result = { 0 };
            for (size_t Index = 0; Index < 32; Index++) {
                Result.Data[Index] = Data[Index] / Second;
            }
            return Result;
        }

        //Splat
        int32& operator<=(const int8_t Second) {
            for (size_t Index = 0; Index < 32; Index++) {
                Data[Index] = Second;
            }
            return *this;
        }

        bool operator==(const int32&) const = delete;
        bool operator!=(const int32&) const = delete;
        bool operator<(const int32&) const = delete;
        bool operator>(const int32&) const = delete;
        bool operator>=(const int32&) const = delete;
        bool operator<=>(const int32&) const = delete;
    };
    #pragma endregion

    //=====================================================================
    // REGISTER VECTORS
    //
    // Each wraps one 128/256-bit register in a struct rather than aliasing the
    // intrinsic type directly. A bare __m128/256 cannot portably carry
    // operators: MSVC declares it as a union, so overloads are legal,
    // while GCC and Clang declare it as a builtin vector type where
    // "First + Second" already means something and an overload is
    // ill-formed. Wrapping makes the operators legal everywhere and lets
    // the deleted comparisons actually apply.
    //
    // Same bytes, same register. Reach through .Raw for any intrinsic
    // this header does not wrap.
    //
    // The integer types are split by lane count to match the storage
    // structs: AVXI4 <-> int4, AVXI8 <-> int8, and so on. A 256-bit
    // integer register carries no lane width of its own, so the width has
    // to live in the type: _mm256_add_epi32 and _mm256_add_epi16 read the
    // same 32 bytes and give different answers. Putting it in the type is
    // also what makes Store() unambiguous, since a return type cannot be
    // overloaded on.
    //=====================================================================
    #pragma region Register_Vectors
    //AVXF3 type, 3 floats
    struct alignas(16) AVXF3 {
        //W is UNSPECIFIED for this type!
        __m128 Raw;

        //Vector-vector
        AVXF3 operator+(const AVXF3& Second) const { return { _mm_add_ps(Raw, Second.Raw) }; }
        AVXF3 operator-(const AVXF3& Second) const { return { _mm_sub_ps(Raw, Second.Raw) }; }
        AVXF3 operator*(const AVXF3& Second) const { return { _mm_mul_ps(Raw, Second.Raw) }; }
        AVXF3 operator/(const AVXF3& Second) const { return { _mm_div_ps(Raw, Second.Raw) }; }

        //Vector-scalar
        AVXF3 operator+(const float Second) const { return { _mm_add_ps(Raw, _mm_set1_ps(Second)) }; }
        AVXF3 operator-(const float Second) const { return { _mm_sub_ps(Raw, _mm_set1_ps(Second)) }; }
        AVXF3 operator*(const float Second) const { return { _mm_mul_ps(Raw, _mm_set1_ps(Second)) }; }
        AVXF3 operator/(const float Second) const { return { _mm_div_ps(Raw, _mm_set1_ps(Second)) }; }

        //Splat
        AVXF3& operator<=(const float Second) {
            Raw = _mm_set1_ps(Second);
            return *this;
        }

        bool operator==(const AVXF3&) const = delete;
        bool operator!=(const AVXF3&) const = delete;
        bool operator<(const AVXF3&) const = delete;
        bool operator>(const AVXF3&) const = delete;
        bool operator>=(const AVXF3&) const = delete;
        bool operator<=>(const AVXF3&) const = delete;
    };
    //AVXF4 type, 4 floats
    struct alignas(16) AVXF4 {
        __m128 Raw;

        //Vector-vector
        AVXF4 operator+(const AVXF4& Second) const { return { _mm_add_ps(Raw, Second.Raw) }; }
        AVXF4 operator-(const AVXF4& Second) const { return { _mm_sub_ps(Raw, Second.Raw) }; }
        AVXF4 operator*(const AVXF4& Second) const { return { _mm_mul_ps(Raw, Second.Raw) }; }
        AVXF4 operator/(const AVXF4& Second) const { return { _mm_div_ps(Raw, Second.Raw) }; }

        //Vector-scalar
        AVXF4 operator+(const float Second) const { return { _mm_add_ps(Raw, _mm_set1_ps(Second)) }; }
        AVXF4 operator-(const float Second) const { return { _mm_sub_ps(Raw, _mm_set1_ps(Second)) }; }
        AVXF4 operator*(const float Second) const { return { _mm_mul_ps(Raw, _mm_set1_ps(Second)) }; }
        AVXF4 operator/(const float Second) const { return { _mm_div_ps(Raw, _mm_set1_ps(Second)) }; }

        //Splat
        AVXF4& operator<=(const float Second) {
            Raw = _mm_set1_ps(Second);
            return *this;
        }

        bool operator==(const AVXF4&) const = delete;
        bool operator!=(const AVXF4&) const = delete;
        bool operator<(const AVXF4&) const = delete;
        bool operator>(const AVXF4&) const = delete;
        bool operator>=(const AVXF4&) const = delete;
        bool operator<=>(const AVXF4&) const = delete;
    };
    //AVXF8 type, 8 floats
    struct alignas(32) AVXF8 {
        __m256 Raw;

        //Vector-vector
        AVXF8 operator+(const AVXF8& Second) const { return { _mm256_add_ps(Raw, Second.Raw) }; }
        AVXF8 operator-(const AVXF8& Second) const { return { _mm256_sub_ps(Raw, Second.Raw) }; }
        AVXF8 operator*(const AVXF8& Second) const { return { _mm256_mul_ps(Raw, Second.Raw) }; }
        AVXF8 operator/(const AVXF8& Second) const { return { _mm256_div_ps(Raw, Second.Raw) }; }

        //Vector-scalar
        AVXF8 operator+(const float Second) const { return { _mm256_add_ps(Raw, _mm256_set1_ps(Second)) }; }
        AVXF8 operator-(const float Second) const { return { _mm256_sub_ps(Raw, _mm256_set1_ps(Second)) }; }
        AVXF8 operator*(const float Second) const { return { _mm256_mul_ps(Raw, _mm256_set1_ps(Second)) }; }
        AVXF8 operator/(const float Second) const { return { _mm256_div_ps(Raw, _mm256_set1_ps(Second)) }; }

        //Splat
        AVXF8& operator<=(const float Second) {
            Raw = _mm256_set1_ps(Second);
            return *this;
        }

        bool operator==(const AVXF8&) const = delete;
        bool operator!=(const AVXF8&) const = delete;
        bool operator<(const AVXF8&) const = delete;
        bool operator>(const AVXF8&) const = delete;
        bool operator>=(const AVXF8&) const = delete;
        bool operator<=>(const AVXF8&) const = delete;
    };
    //AVXD4 type, 4 doubles
    struct alignas(32) AVXD4 {
        __m256d Raw;

        //Vector-vector
        AVXD4 operator+(const AVXD4& Second) const { return { _mm256_add_pd(Raw, Second.Raw) }; }
        AVXD4 operator-(const AVXD4& Second) const { return { _mm256_sub_pd(Raw, Second.Raw) }; }
        AVXD4 operator*(const AVXD4& Second) const { return { _mm256_mul_pd(Raw, Second.Raw) }; }
        AVXD4 operator/(const AVXD4& Second) const { return { _mm256_div_pd(Raw, Second.Raw) }; }

        //Vector-scalar
        AVXD4 operator+(const double Second) const { return { _mm256_add_pd(Raw, _mm256_set1_pd(Second)) }; }
        AVXD4 operator-(const double Second) const { return { _mm256_sub_pd(Raw, _mm256_set1_pd(Second)) }; }
        AVXD4 operator*(const double Second) const { return { _mm256_mul_pd(Raw, _mm256_set1_pd(Second)) }; }
        AVXD4 operator/(const double Second) const { return { _mm256_div_pd(Raw, _mm256_set1_pd(Second)) }; }

        //Splat
        AVXD4& operator<=(const double Second) {
            Raw = _mm256_set1_pd(Second);
            return *this;
        }

        bool operator==(const AVXD4&) const = delete;
        bool operator!=(const AVXD4&) const = delete;
        bool operator<(const AVXD4&) const = delete;
        bool operator>(const AVXD4&) const = delete;
        bool operator>=(const AVXD4&) const = delete;
        bool operator<=>(const AVXD4&) const = delete;
    };

    //AVXI4 type, 4 int64s
    struct alignas(32) AVXI4 {
        __m256i Raw;

        //Vector-vector
        AVXI4 operator+(const AVXI4& Second) const { return { _mm256_add_epi64(Raw, Second.Raw) }; }
        AVXI4 operator-(const AVXI4& Second) const { return { _mm256_sub_epi64(Raw, Second.Raw) }; }

        //Vector-scalar
        AVXI4 operator+(const int64_t Second) const {
            return { _mm256_add_epi64(Raw, _mm256_set1_epi64x(static_cast<long long>(Second))) };
        }
        AVXI4 operator-(const int64_t Second) const {
            return { _mm256_sub_epi64(Raw, _mm256_set1_epi64x(static_cast<long long>(Second))) };
        }

        //Bitwise
        AVXI4 operator&(const AVXI4& Second) const { return { _mm256_and_si256(Raw, Second.Raw) }; }
        AVXI4 operator|(const AVXI4& Second) const { return { _mm256_or_si256(Raw, Second.Raw) }; }
        AVXI4 operator^(const AVXI4& Second) const { return { _mm256_xor_si256(Raw, Second.Raw) }; }

        //Splat
        AVXI4& operator<=(const int64_t Second) {
            Raw = _mm256_set1_epi64x(static_cast<long long>(Second));
            return *this;
        }

        //64-bit lane multiply needs AVX-512DQ. No integer divide exists at
        //any lane width, in any generation.
        AVXI4 operator*(const AVXI4) const = delete;
        AVXI4 operator*(const int64_t) const = delete;
        AVXI4 operator/(const AVXI4) const = delete;
        AVXI4 operator/(const int64_t) const = delete;

        bool operator==(const AVXI4&) const = delete;
        bool operator!=(const AVXI4&) const = delete;
        bool operator<(const AVXI4&) const = delete;
        bool operator>(const AVXI4&) const = delete;
        bool operator>=(const AVXI4&) const = delete;
        bool operator<=>(const AVXI4&) const = delete;
    };
    //AVXI8 type, 8 int32s
    struct alignas(32) AVXI8 {
        __m256i Raw;

        //Vector-vector
        AVXI8 operator+(const AVXI8& Second) const { return { _mm256_add_epi32(Raw, Second.Raw) }; }
        AVXI8 operator-(const AVXI8& Second) const { return { _mm256_sub_epi32(Raw, Second.Raw) }; }
        AVXI8 operator*(const AVXI8& Second) const { return { _mm256_mullo_epi32(Raw, Second.Raw) }; }

        //Vector-scalar
        AVXI8 operator+(const int32_t Second) const {
            return { _mm256_add_epi32(Raw, _mm256_set1_epi32(static_cast<int>(Second))) };
        }
        AVXI8 operator-(const int32_t Second) const {
            return { _mm256_sub_epi32(Raw, _mm256_set1_epi32(static_cast<int>(Second))) };
        }
        AVXI8 operator*(const int32_t Second) const {
            return { _mm256_mullo_epi32(Raw, _mm256_set1_epi32(static_cast<int>(Second))) };
        }

        //Bitwise
        AVXI8 operator&(const AVXI8& Second) const { return { _mm256_and_si256(Raw, Second.Raw) }; }
        AVXI8 operator|(const AVXI8& Second) const { return { _mm256_or_si256(Raw, Second.Raw) }; }
        AVXI8 operator^(const AVXI8& Second) const { return { _mm256_xor_si256(Raw, Second.Raw) }; }

        //Splat
        AVXI8& operator<=(const int32_t Second) {
            Raw = _mm256_set1_epi32(static_cast<int>(Second));
            return *this;
        }

        //No integer divide exists.
        AVXI8 operator/(const AVXI8) const = delete;
        AVXI8 operator/(const int32_t) const = delete;
        bool operator==(const AVXI8&) const = delete;
        bool operator!=(const AVXI8&) const = delete;
        bool operator<(const AVXI8&) const = delete;
        bool operator>(const AVXI8&) const = delete;
        bool operator>=(const AVXI8&) const = delete;
        bool operator<=>(const AVXI8&) const = delete;
    };
    //AVXI16 type, 16 int16s
    struct alignas(32) AVXI16 {
        __m256i Raw;

        //Vector-vector
        AVXI16 operator+(const AVXI16& Second) const { return { _mm256_add_epi16(Raw, Second.Raw) }; }
        AVXI16 operator-(const AVXI16& Second) const { return { _mm256_sub_epi16(Raw, Second.Raw) }; }
        AVXI16 operator*(const AVXI16& Second) const { return { _mm256_mullo_epi16(Raw, Second.Raw) }; }

        //Vector-scalar
        AVXI16 operator+(const int16_t Second) const { return { _mm256_add_epi16(Raw, _mm256_set1_epi16(Second)) }; }
        AVXI16 operator-(const int16_t Second) const { return { _mm256_sub_epi16(Raw, _mm256_set1_epi16(Second)) }; }
        AVXI16 operator*(const int16_t Second) const { return { _mm256_mullo_epi16(Raw, _mm256_set1_epi16(Second)) }; }

        //Bitwise
        AVXI16 operator&(const AVXI16& Second) const { return { _mm256_and_si256(Raw, Second.Raw) }; }
        AVXI16 operator|(const AVXI16& Second) const { return { _mm256_or_si256(Raw, Second.Raw) }; }
        AVXI16 operator^(const AVXI16& Second) const { return { _mm256_xor_si256(Raw, Second.Raw) }; }

        //Splat
        AVXI16& operator<=(const int16_t Second) {
            Raw = _mm256_set1_epi16(Second);
            return *this;
        }

        //No integer divide exists.
        AVXI16 operator/(const AVXI16) const = delete;
        AVXI16 operator/(const int16_t) const = delete;

        bool operator==(const AVXI16&) const = delete;
        bool operator!=(const AVXI16&) const = delete;
        bool operator<(const AVXI16&) const = delete;
        bool operator>(const AVXI16&) const = delete;
        bool operator>=(const AVXI16&) const = delete;
        bool operator<=>(const AVXI16&) const = delete;
    };
    //AVXI32 type, 32 int8s
    struct alignas(32) AVXI32 {
        __m256i Raw;

        //Vector-vector
        AVXI32 operator+(const AVXI32& Second) const { return { _mm256_add_epi8(Raw, Second.Raw) }; }
        AVXI32 operator-(const AVXI32& Second) const { return { _mm256_sub_epi8(Raw, Second.Raw) }; }

        //Vector-scalar
        AVXI32 operator+(const int8_t Second) const { return { _mm256_add_epi8(Raw, _mm256_set1_epi8(Second)) }; }
        AVXI32 operator-(const int8_t Second) const { return { _mm256_sub_epi8(Raw, _mm256_set1_epi8(Second)) }; }

        //Bitwise
        AVXI32 operator&(const AVXI32& Second) const { return { _mm256_and_si256(Raw, Second.Raw) }; }
        AVXI32 operator|(const AVXI32& Second) const { return { _mm256_or_si256(Raw, Second.Raw) }; }
        AVXI32 operator^(const AVXI32& Second) const { return { _mm256_xor_si256(Raw, Second.Raw) }; }

        //Splat
        AVXI32& operator<=(const int8_t Second) {
            Raw = _mm256_set1_epi8(Second);
            return *this;
        }

        //8-bit lane multiply does not exist in any AVX generation. No
        //integer divide exists either.
        AVXI32 operator*(const AVXI32) const = delete;
        AVXI32 operator*(const int8_t) const = delete;
        AVXI32 operator/(const AVXI32) const = delete;
        AVXI32 operator/(const int8_t) const = delete;

        bool operator==(const AVXI32&) const = delete;
        bool operator!=(const AVXI32&) const = delete;
        bool operator<(const AVXI32&) const = delete;
        bool operator>(const AVXI32&) const = delete;
        bool operator>=(const AVXI32&) const = delete;
        bool operator<=>(const AVXI32&) const = delete;
    };
    #pragma endregion

    //=====================================================================
    // LOAD / STORE
    //
    // Storage vectors hold values in memory; register vectors hold them in
    // a 128 or 256-bit register and carry the SIMD instructions. Move between them
    // with LoadAVX and StoreAVX.
    // 
    // Every storage type that fills a whole register carries aligned types,
    // so the aligned intrinsics are safe on all of these.
    //=====================================================================
    #pragma region Load_Store
    //Loads a float3
    inline void LoadAVX(const float3& Source, AVXF3& Destination) {
        Destination = { _mm_setr_ps(Source.x, Source.y, Source.z, 0.0f) };
    }
    //Loads a float4
    inline void LoadAVX(const float4& Source, AVXF4& Destination) {
        Destination = { _mm_load_ps(&Source.x) };
    }
    //Loads a float8
    inline void LoadAVX(const float8& Source, AVXF8& Destination) {//Load a float8 into vector memory
        Destination = { _mm256_load_ps(reinterpret_cast<const float*>(&Source.Data)) };
    }
    //Loads a double4
    inline void LoadAVX(const double4& Source, AVXD4& Destination) {//Load a double4 into vector memory
        Destination = { _mm256_load_pd(reinterpret_cast<const double*>(&Source)) };
    }
    //Loads an int4
    inline void LoadAVX(const int4& Source, AVXI4& Destination) {//Load an int4 into vector memory
        Destination = { _mm256_load_si256(reinterpret_cast<const __m256i*>(&Source)) };
    }
    //Loads an int8
    inline void LoadAVX(const int8& Source, AVXI8& Destination) {//Load an int8 into vector memory
        Destination = { _mm256_load_si256(reinterpret_cast<const __m256i*>(&Source.Data)) };
    }
    //Loads an int16
    inline void LoadAVX(const int16& Source, AVXI16& Destination) {//Load an int16 into vector memory
        Destination = { _mm256_load_si256(reinterpret_cast<const __m256i*>(&Source)) };
    }
    //Loads an int32
    inline void LoadAVX(const int32& Source, AVXI32& Destination) {//Load an int32 into vector memory
        Destination = { _mm256_load_si256(reinterpret_cast<const __m256i*>(&Source)) };
    }

    //Builds an AVXF8 from two float4's
    inline void LoadAVX(const float4& A, const float4& B, AVXF8& Destination) {//Load two float4's into vector memory
        alignas(32) float Data[8] = {
            A.x, A.y, A.z, A.w,
            B.x, B.y, B.z, B.w
        };
        Destination = { _mm256_load_ps(Data) };
    }
    //Builds an AVXF8 from four float2's
    inline void LoadAVX(const float2& A, const float2& B, const float2& C, const float2& D, AVXF8& Destination) {//Load four float2's into vector memory
        alignas(32) float Data[8] = {
            A.x, A.y, B.x, B.y,
            C.x, C.y, D.x, D.y
        };
        Destination = { _mm256_load_ps(Data) };
    }
    //Builds an AVXD4 from two double2's
    inline void LoadAVX(const double2& A, const double2& B, AVXD4& Destination) {//Load two double2's into vector memory
        alignas(32) double Data[4] = { A.x, A.y, B.x, B.y };
        Destination = { _mm256_load_pd(Data) };
    }

    //Store a float3
    inline void StoreAVX(const AVXF3& Source, float3& Destination) {
        alignas(16) float Temp[4];
        _mm_store_ps(Temp, Source.Raw);
        Destination = { Temp[0], Temp[1], Temp[2] };
    }
    //Store a float4
    inline void StoreAVX(const AVXF4& Source, float4& Destination) {
        _mm_store_ps(&Destination.x, Source.Raw);
    }
    //Store a float8
    inline void StoreAVX(const AVXF8& Source, float8& Destination) {//Store a float8
        _mm256_store_ps(Destination.Data, Source.Raw);
    }
    //Store a double4
    inline void StoreAVX(const AVXD4& Source, double4& Destination) {//Store a double4
        _mm256_store_pd(&Destination.x, Source.Raw);
    }
    //Store an int4
    inline void StoreAVX(const AVXI4& Source, int4& Destination) {//Store an int4
        _mm256_store_si256(reinterpret_cast<__m256i*>(&Destination), Source.Raw);
    }
    //Store an int8
    inline void StoreAVX(const AVXI8& Source, int8& Destination) {//Store an int8
        _mm256_store_si256(reinterpret_cast<__m256i*>(&Destination.Data), Source.Raw);
    }
    //Store an int16
    inline void StoreAVX(const AVXI16& Source, int16& Destination) {//Store an int16
        _mm256_store_si256(reinterpret_cast<__m256i*>(&Destination), Source.Raw);
    }
    //Store an int32
    inline void StoreAVX(const AVXI32& Source, int32& Destination) {//Store an int32
        _mm256_store_si256(reinterpret_cast<__m256i*>(&Destination), Source.Raw);
    }

    //Two AVXF4 -> one AVXF8
    inline void Combine(const AVXF4& Lower, const AVXF4& Upper, AVXF8& Destination) {
        Destination = { _mm256_insertf128_ps(_mm256_castps128_ps256(Lower.Raw), Upper.Raw, 1) };
    }
    //One AVXF8 -> two AVXF4
    inline void Split(const AVXF8& Source, AVXF4& Lower, AVXF4& Upper) {
        Lower = { _mm256_castps256_ps128(Source.Raw) };
        Upper = { _mm256_extractf128_ps(Source.Raw, 1) };
    }
    #pragma endregion

    //=====================================================================
    // GEOMETRY - storage vectors
    //
    // Plain scalar code acting on ONE vector at a time. Normalize,
    // Reflect and the Distance family assume well-conditioned inputs -
    // a malformed vector is the caller's problem.
    //=====================================================================
    #pragma region Storage_Geometry
    inline float DotProduct(const float2& First, const float2& Second) {
        return First.x * Second.x + First.y * Second.y;
    }
    inline float DotProduct(const float3& First, const float3& Second) {
        return First.x * Second.x + First.y * Second.y + First.z * Second.z;
    }
    inline float DotProduct(const float4& First, const float4& Second) {
        return First.x * Second.x + First.y * Second.y + First.z * Second.z + First.w * Second.w;
    }
    inline double DotProduct(const double2& First, const double2& Second) {
        return First.x * Second.x + First.y * Second.y;
    }
    inline double DotProduct(const double3& First, const double3& Second) {
        return First.x * Second.x + First.y * Second.y + First.z * Second.z;
    }
    inline double DotProduct(const double4& First, const double4& Second) {
        return First.x * Second.x + First.y * Second.y + First.z * Second.z + First.w * Second.w;
    }

    inline void CrossProduct(const float3& A, const float3& B, float3& Destination) {
        Destination = {
            A.y * B.z - A.z * B.y,
            A.z * B.x - A.x * B.z,
            A.x * B.y - A.y * B.x
        };
    }
    inline void CrossProduct(const double3& A, const double3& B, double3& Destination) {
        Destination = {
            A.y * B.z - A.z * B.y,
            A.z * B.x - A.x * B.z,
            A.x * B.y - A.y * B.x
        };
    }

    inline float LengthSquared(const float2& Source) { return DotProduct(Source, Source); }
    inline float LengthSquared(const float3& Source) { return DotProduct(Source, Source); }
    inline float LengthSquared(const float4& Source) { return DotProduct(Source, Source); }
    inline double LengthSquared(const double2& Source) { return DotProduct(Source, Source); }
    inline double LengthSquared(const double3& Source) { return DotProduct(Source, Source); }
    inline double LengthSquared(const double4& Source) { return DotProduct(Source, Source); }

    inline float Length(const float2& Source) { return sqrtf(LengthSquared(Source)); }
    inline float Length(const float3& Source) { return sqrtf(LengthSquared(Source)); }
    inline float Length(const float4& Source) { return sqrtf(LengthSquared(Source)); }
    inline double Length(const double2& Source) { return sqrt(LengthSquared(Source)); }
    inline double Length(const double3& Source) { return sqrt(LengthSquared(Source)); }
    inline double Length(const double4& Source) { return sqrt(LengthSquared(Source)); }

    inline void Normalize(const float2& Source, float2& Destination) { Destination = Source / Length(Source); }
    inline void Normalize(const float3& Source, float3& Destination) { Destination = Source / Length(Source); }
    inline void Normalize(const float4& Source, float4& Destination) { Destination = Source / Length(Source); }
    inline void Normalize(const double2& Source, double2& Destination) { Destination = Source / Length(Source); }
    inline void Normalize(const double3& Source, double3& Destination) { Destination = Source / Length(Source); }
    inline void Normalize(const double4& Source, double4& Destination) { Destination = Source / Length(Source); }

    inline float DistanceSquared(const float2& First, const float2& Second) { return LengthSquared(First - Second); }
    inline float DistanceSquared(const float3& First, const float3& Second) { return LengthSquared(First - Second); }
    inline float DistanceSquared(const float4& First, const float4& Second) { return LengthSquared(First - Second); }
    inline double DistanceSquared(const double2& First, const double2& Second) { return LengthSquared(First - Second); }
    inline double DistanceSquared(const double3& First, const double3& Second) { return LengthSquared(First - Second); }
    inline double DistanceSquared(const double4& First, const double4& Second) { return LengthSquared(First - Second); }

    inline float Distance(const float2& First, const float2& Second) { return Length(First - Second); }
    inline float Distance(const float3& First, const float3& Second) { return Length(First - Second); }
    inline float Distance(const float4& First, const float4& Second) { return Length(First - Second); }
    inline double Distance(const double2& First, const double2& Second) { return Length(First - Second); }
    inline double Distance(const double3& First, const double3& Second) { return Length(First - Second); }
    inline double Distance(const double4& First, const double4& Second) { return Length(First - Second); }

    inline void Lerp(const float2& A, const float2& B, float2& Destination, const float Amount) {
        Destination = A + (B - A) * Amount;
    }
    inline void Lerp(const float3& A, const float3& B, float3& Destination, const float Amount) {
        Destination = A + (B - A) * Amount;
    }
    inline void Lerp(const float4& A, const float4& B, float4& Destination, const float Amount) {
        Destination = A + (B - A) * Amount;
    }
    inline void Lerp(const double2& A, const double2& B, double2& Destination, const double Amount) {
        Destination = A + (B - A) * Amount;
    }
    inline void Lerp(const double3& A, const double3& B, double3& Destination, const double Amount) {
        Destination = A + (B - A) * Amount;
    }
    inline void Lerp(const double4& A, const double4& B, double4& Destination, const double Amount) {
        Destination = A + (B - A) * Amount;
    }

    inline void Reflect(const float2& Incident, const float2& SurfaceNormal, float2& Destination) {
        Destination = Incident - SurfaceNormal * (2.0f * DotProduct(Incident, SurfaceNormal));
    }
    inline void Reflect(const float3& Incident, const float3& SurfaceNormal, float3& Destination) {
        Destination = Incident - SurfaceNormal * (2.0f * DotProduct(Incident, SurfaceNormal));
    }
    inline void Reflect(const double2& Incident, const double2& SurfaceNormal, double2& Destination) {
        Destination = Incident - SurfaceNormal * (2.0 * DotProduct(Incident, SurfaceNormal));
    }
    inline void Reflect(const double3& Incident, const double3& SurfaceNormal, double3& Destination) {
        Destination = Incident - SurfaceNormal * (2.0 * DotProduct(Incident, SurfaceNormal));
    }
    #pragma endregion

    //=====================================================================
    // PER-LANE MATHS - register vectors
    //
    // Every function here acts on all lanes at once and returns a full
    // register.
    //
    // HorizontalSum is provided for the cases where you need
    // to collapse a register, but it is a reduction and costs accordingly
    // - keep it out of inner loops.
    //=====================================================================
    #pragma region Register_Maths
    //Float-128, float3
    inline void SquareRoot(const AVXF3& Source, AVXF3& Destination) { Destination = { _mm_sqrt_ps(Source.Raw) }; }
    inline void Minimum(const AVXF3& A, const AVXF3& B, AVXF3& Destination) { Destination = { _mm_min_ps(A.Raw, B.Raw) }; }
    inline void Maximum(const AVXF3& A, const AVXF3& B, AVXF3& Destination) { Destination = { _mm_max_ps(A.Raw, B.Raw) }; }
    inline void AbsoluteValue(const AVXF3& Source, AVXF3& Destination) { Destination = { _mm_andnot_ps(_mm_set1_ps(-0.0f), Source.Raw) }; }
    inline void Negate(const AVXF3& Source, AVXF3& Destination) { Destination = { _mm_xor_ps(Source.Raw, _mm_set1_ps(-0.0f)) }; }
    inline void Floor(const AVXF3& Source, AVXF3& Destination) { Destination = { _mm_floor_ps(Source.Raw) }; }
    inline void Ceiling(const AVXF3& Source, AVXF3& Destination) { Destination = { _mm_ceil_ps(Source.Raw) }; }
    inline void RoundNearest(const AVXF3& Source, AVXF3& Destination) {
        Destination = { _mm_round_ps(Source.Raw, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
    }
    inline void Truncate(const AVXF3& Source, AVXF3& Destination) {
        Destination = { _mm_round_ps(Source.Raw, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
    }
    inline void Clamp(const AVXF3& Source, AVXF3& Destination, const AVXF3& Min, const AVXF3& Max) {
        AVXF3 Bounded;
        Maximum(Source, Min, Bounded);
        Minimum(Bounded, Max, Destination);
    }
    inline void Lerp(const AVXF3& A, const AVXF3& B, AVXF3& Destination, const float Amount) { Destination = A + (B - A) * Amount; }
    //Float4
    inline void SquareRoot(const AVXF4& Source, AVXF4& Destination) { Destination = { _mm_sqrt_ps(Source.Raw) }; }
    inline void Minimum(const AVXF4& A, const AVXF4& B, AVXF4& Destination) { Destination = { _mm_min_ps(A.Raw, B.Raw) }; }
    inline void Maximum(const AVXF4& A, const AVXF4& B, AVXF4& Destination) { Destination = { _mm_max_ps(A.Raw, B.Raw) }; }
    inline void AbsoluteValue(const AVXF4& Source, AVXF4& Destination) { Destination = { _mm_andnot_ps(_mm_set1_ps(-0.0f), Source.Raw) }; }
    inline void Negate(const AVXF4& Source, AVXF4& Destination) { Destination = { _mm_xor_ps(Source.Raw, _mm_set1_ps(-0.0f)) }; }
    inline void Floor(const AVXF4& Source, AVXF4& Destination) { Destination = { _mm_floor_ps(Source.Raw) }; }
    inline void Ceiling(const AVXF4& Source, AVXF4& Destination) { Destination = { _mm_ceil_ps(Source.Raw) }; }
    inline void RoundNearest(const AVXF4& Source, AVXF4& Destination) {
        Destination = { _mm_round_ps(Source.Raw, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
    }
    inline void Truncate(const AVXF4& Source, AVXF4& Destination) {
        Destination = { _mm_round_ps(Source.Raw, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
    }
    inline void Clamp(const AVXF4& Source, AVXF4& Destination, const AVXF4& Min, const AVXF4& Max) {
        AVXF4 Bounded;
        Maximum(Source, Min, Bounded);
        Minimum(Bounded, Max, Destination);
    }
    inline void Lerp(const AVXF4& A, const AVXF4& B, AVXF4& Destination, const float Amount) { Destination = A + (B - A) * Amount; }

    //Float-256
    inline void SquareRoot(const AVXF8& Source, AVXF8& Destination) { Destination = { _mm256_sqrt_ps(Source.Raw) }; }
    inline void Minimum(const AVXF8& A, const AVXF8& B, AVXF8& Destination) { Destination = { _mm256_min_ps(A.Raw, B.Raw) }; }
    inline void Maximum(const AVXF8& A, const AVXF8& B, AVXF8& Destination) { Destination = { _mm256_max_ps(A.Raw, B.Raw) }; }
    inline void AbsoluteValue(const AVXF8& Source, AVXF8& Destination) { Destination = { _mm256_andnot_ps(_mm256_set1_ps(-0.0f), Source.Raw) }; }
    inline void Negate(const AVXF8& Source, AVXF8& Destination) { Destination = { _mm256_xor_ps(Source.Raw, _mm256_set1_ps(-0.0f)) }; }
    inline void Floor(const AVXF8& Source, AVXF8& Destination) { Destination = { _mm256_floor_ps(Source.Raw) }; }
    inline void Ceiling(const AVXF8& Source, AVXF8& Destination) { Destination = { _mm256_ceil_ps(Source.Raw) }; }
    inline void RoundNearest(const AVXF8& Source, AVXF8& Destination) {
        Destination = { _mm256_round_ps(Source.Raw, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
    }
    inline void Truncate(const AVXF8& Source, AVXF8& Destination) {
        Destination = { _mm256_round_ps(Source.Raw, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
    }
    inline void Clamp(const AVXF8& Source, AVXF8& Destination, const AVXF8& Min, const AVXF8& Max) {
        AVXF8 Bounded;
        Maximum(Source, Min, Bounded);
        Minimum(Bounded, Max, Destination);
    }
    inline void Lerp(const AVXF8& A, const AVXF8& B, AVXF8& Destination, const float Amount) { Destination = A + (B - A) * Amount; }

    //Double
    inline void SquareRoot(const AVXD4& Source, AVXD4& Destination) { Destination = { _mm256_sqrt_pd(Source.Raw) }; }
    inline void Minimum(const AVXD4& A, const AVXD4& B, AVXD4& Destination) { Destination = { _mm256_min_pd(A.Raw, B.Raw) }; }
    inline void Maximum(const AVXD4& A, const AVXD4& B, AVXD4& Destination) { Destination = { _mm256_max_pd(A.Raw, B.Raw) }; }
    inline void AbsoluteValue(const AVXD4& Source, AVXD4& Destination) { Destination = { _mm256_andnot_pd(_mm256_set1_pd(-0.0), Source.Raw) }; }
    inline void Negate(const AVXD4& Source, AVXD4& Destination) { Destination = { _mm256_xor_pd(Source.Raw, _mm256_set1_pd(-0.0)) }; }
    inline void Floor(const AVXD4& Source, AVXD4& Destination) { Destination = { _mm256_floor_pd(Source.Raw) }; }
    inline void Ceiling(const AVXD4& Source, AVXD4& Destination) { Destination = { _mm256_ceil_pd(Source.Raw) }; }
    inline void RoundNearest(const AVXD4& Source, AVXD4& Destination) {
        Destination = { _mm256_round_pd(Source.Raw, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
    }
    inline void Truncate(const AVXD4& Source, AVXD4& Destination) {
        Destination = { _mm256_round_pd(Source.Raw, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
    }
    inline void Clamp(const AVXD4& Source, AVXD4& Destination, const AVXD4& Min, const AVXD4& Max) {
        AVXD4 Bounded;
        Maximum(Source, Min, Bounded);
        Minimum(Bounded, Max, Destination);
    }
    inline void Lerp(const AVXD4& A, const AVXD4& B, AVXD4& Destination, const double Amount) { Destination = A + (B - A) * Amount; }

    //~~~~~~~ 4x64bit
    //All three need AVX - 512F + VL, so are unavailable in this version
    inline void Minimum(const AVXI4&, const AVXI4&, AVXI4&) = delete;
    inline void UnsignedMinimum(const AVXI4&, const AVXI4&, AVXI4&) = delete;
    inline void Maximum(const AVXI4&, const AVXI4&, AVXI4&) = delete;
    inline void UnsignedMaximum(const AVXI4&, const AVXI4&, AVXI4&) = delete;
    inline void AbsoluteValue(const AVXI4&, AVXI4&) = delete;
    //~~~~~~~ 8x32bit
    inline void Minimum(const AVXI8& A, const AVXI8& B, AVXI8& Destination) { Destination = { _mm256_min_epi32(A.Raw, B.Raw) }; }
    inline void UnsignedMinimum(const AVXI8& A, const AVXI8& B, AVXI8& Destination) { Destination = { _mm256_min_epu32(A.Raw, B.Raw) }; }
    inline void Maximum(const AVXI8& A, const AVXI8& B, AVXI8& Destination) { Destination = { _mm256_max_epi32(A.Raw, B.Raw) }; }
    inline void UnsignedMaximum(const AVXI8& A, const AVXI8& B, AVXI8& Destination) { Destination = { _mm256_max_epu32(A.Raw, B.Raw) }; }
    inline void AbsoluteValue(const AVXI8& Source, AVXI8& Destination) { Destination = { _mm256_abs_epi32(Source.Raw) }; }
    //~~~~~~~ 16x16bit
    inline void Minimum(const AVXI16& A, const AVXI16& B, AVXI16& Destination) { Destination = { _mm256_min_epi16(A.Raw, B.Raw) }; }
    inline void UnsignedMinimum(const AVXI16& A, const AVXI16& B, AVXI16& Destination) { Destination = { _mm256_min_epu16(A.Raw, B.Raw) }; }
    inline void Maximum(const AVXI16& A, const AVXI16& B, AVXI16& Destination) { Destination = { _mm256_max_epi16(A.Raw, B.Raw) }; }
    inline void UnsignedMaximum(const AVXI16& A, const AVXI16& B, AVXI16& Destination) { Destination = { _mm256_max_epu16(A.Raw, B.Raw) }; }
    inline void AbsoluteValue(const AVXI16& Source, AVXI16& Destination) { Destination = { _mm256_abs_epi16(Source.Raw) }; }
    //~~~~~~~ 32x8bit
    inline void Minimum(const AVXI32& A, const AVXI32& B, AVXI32& Destination) { Destination = { _mm256_min_epi8(A.Raw, B.Raw) }; }
    inline void UnsignedMinimum(const AVXI32& A, const AVXI32& B, AVXI32& Destination) { Destination = { _mm256_min_epu8(A.Raw, B.Raw) }; }
    inline void Maximum(const AVXI32& A, const AVXI32& B, AVXI32& Destination) { Destination = { _mm256_max_epi8(A.Raw, B.Raw) }; }
    inline void UnsignedMaximum(const AVXI32& A, const AVXI32& B, AVXI32& Destination) { Destination = { _mm256_max_epu8(A.Raw, B.Raw) }; }
    inline void AbsoluteValue(const AVXI32& Source, AVXI32& Destination) { Destination = { _mm256_abs_epi8(Source.Raw) }; }

    //~12-bit approximations
    inline void ReciprocalFast(const AVXF3& Source, AVXF3& Destination) { Destination = { _mm_rcp_ps(Source.Raw) }; }
    inline void ReciprocalFast(const AVXF4& Source, AVXF4& Destination) { Destination = { _mm_rcp_ps(Source.Raw) }; }
    inline void ReciprocalFast(const AVXF8& Source, AVXF8& Destination) { Destination = { _mm256_rcp_ps(Source.Raw) }; }
    inline void ReciprocalSquareRootFast(const AVXF3& Source, AVXF3& Destination) { Destination = { _mm_rsqrt_ps(Source.Raw) }; }
    inline void ReciprocalSquareRootFast(const AVXF4& Source, AVXF4& Destination) { Destination = { _mm_rsqrt_ps(Source.Raw) }; }
    inline void ReciprocalSquareRootFast(const AVXF8& Source, AVXF8& Destination) { Destination = { _mm256_rsqrt_ps(Source.Raw) }; }

    //Fused multiply-add
    inline void MultiplyAdd(const AVXF3& A, const AVXF3& B, const AVXF3& C, AVXF3& Destination) {
        Destination = { _mm_fmadd_ps(A.Raw, B.Raw, C.Raw) };
    }
    inline void MultiplySubtract(const AVXF3& A, const AVXF3& B, const AVXF3& C, AVXF3& Destination) {
        Destination = { _mm_fmsub_ps(A.Raw, B.Raw, C.Raw) };
    }
    inline void MultiplyAdd(const AVXF4& A, const AVXF4& B, const AVXF4& C, AVXF4& Destination) {
        Destination = { _mm_fmadd_ps(A.Raw, B.Raw, C.Raw) };
    }
    inline void MultiplySubtract(const AVXF4& A, const AVXF4& B, const AVXF4& C, AVXF4& Destination) {
        Destination = { _mm_fmsub_ps(A.Raw, B.Raw, C.Raw) };
    }
    inline void MultiplyAdd(const AVXF8& A, const AVXF8& B, const AVXF8& C, AVXF8& Destination) {
        Destination = { _mm256_fmadd_ps(A.Raw, B.Raw, C.Raw) };
    }
    inline void MultiplySubtract(const AVXF8& A, const AVXF8& B, const AVXF8& C, AVXF8& Destination) {
        Destination = { _mm256_fmsub_ps(A.Raw, B.Raw, C.Raw) };
    }
    inline void MultiplyAdd(const AVXD4& A, const AVXD4& B, const AVXD4& C, AVXD4& Destination) {
        Destination = { _mm256_fmadd_pd(A.Raw, B.Raw, C.Raw) };
    }
    inline void MultiplySubtract(const AVXD4& A, const AVXD4& B, const AVXD4& C, AVXD4& Destination) {
        Destination = { _mm256_fmsub_pd(A.Raw, B.Raw, C.Raw) };
    }

    //Reductions
    inline float HorizontalSum(const AVXF3& Source) {
        __m128 Total = _mm_add_ss(Source.Raw, _mm_shuffle_ps(Source.Raw, Source.Raw, _MM_SHUFFLE(0, 0, 0, 1)));
        Total = _mm_add_ss(Total, _mm_movehl_ps(Source.Raw, Source.Raw));
        return _mm_cvtss_f32(Total);
    }
    inline float HorizontalSum(const AVXF4& Source) {
        __m128 Total = _mm_add_ps(Source.Raw, _mm_movehl_ps(Source.Raw, Source.Raw));
        Total = _mm_add_ss(Total, _mm_shuffle_ps(Total, Total, 1));
        return _mm_cvtss_f32(Total);
    }
    inline float HorizontalSum(const AVXF8& Source) {
        const __m128 Lower = _mm256_castps256_ps128(Source.Raw);
        const __m128 Upper = _mm256_extractf128_ps(Source.Raw, 1);
        __m128 Total = _mm_add_ps(Lower, Upper);
        Total = _mm_add_ps(Total, _mm_movehl_ps(Total, Total));
        Total = _mm_add_ss(Total, _mm_shuffle_ps(Total, Total, 1));
        return _mm_cvtss_f32(Total);
    }
    inline double HorizontalSum(const AVXD4& Source) {
        const __m128d Lower = _mm256_castpd256_pd128(Source.Raw);
        const __m128d Upper = _mm256_extractf128_pd(Source.Raw, 1);
        const __m128d Total = _mm_add_pd(Lower, Upper);
        return _mm_cvtsd_f64(_mm_add_sd(Total, _mm_unpackhi_pd(Total, Total)));
    }

    #pragma endregion

    //=====================================================================
    // GEOMETRY - register vectors
    //
    // The dot product is defined in any number of dimensions, so this
    // treats AVXF8 as one 8-component vector and AVXD4 as one 4-component
    // vector. The result is broadcast to every lane rather than returned
    // as a scalar, so it feeds straight back into register arithmetic
    // with no trip through a scalar register - which is what makes
    // Normalize below a pure register operation. 
    // 
    // Beware that DualDot will interleave the results. Every even 
    // index member is the result of A0~B0, every odd is A1~B1.
    //=====================================================================
    #pragma region Register_Geometry
    inline void DotProduct(const AVXF3& A, const AVXF3& B, AVXF3& Destination) {
        Destination = { _mm_dp_ps(A.Raw, B.Raw, 0x7F) };
    }
    inline void DotProduct(const AVXF4& A, const AVXF4& B, AVXF4& Destination) {
        Destination = { _mm_dp_ps(A.Raw, B.Raw, 0xFF) };
    }
    inline void DotProduct(const AVXF8& A, const AVXF8& B, AVXF8& Destination) {
        __m256 Temp = _mm256_mul_ps(A.Raw, B.Raw);
        Temp = _mm256_hadd_ps(Temp, Temp); //adjacent pairs
        Temp = _mm256_hadd_ps(Temp, Temp); //each half now holds its own 4-sum
        Destination = { _mm256_add_ps(Temp, _mm256_permute2f128_ps(Temp, Temp, 0x01)) };
    }
    inline void DotProduct(const AVXD4& A, const AVXD4& B, AVXD4& Destination) {
        __m256d Temp = _mm256_mul_pd(A.Raw, B.Raw);
        Temp = _mm256_hadd_pd(Temp, Temp);
        Destination = { _mm256_add_pd(Temp, _mm256_permute2f128_pd(Temp, Temp, 0x01)) };
    }

    inline void DualDot(const AVXF8& A0, const AVXF8& B0, const AVXF8& A1, const AVXF8& B1, AVXF8& Destination) {
        __m256 Temp = _mm256_hadd_ps(_mm256_mul_ps(A0.Raw, B0.Raw), _mm256_mul_ps(A1.Raw, B1.Raw));
        Temp = _mm256_hadd_ps(Temp, Temp);
        Destination = { _mm256_add_ps(Temp, _mm256_permute2f128_ps(Temp, Temp, 0x01)) };
    }
    inline void DualDot(const AVXD4& A0, const AVXD4& B0, const AVXD4& A1, const AVXD4& B1, AVXD4& Destination) {
        const __m256d Temp = _mm256_hadd_pd(_mm256_mul_pd(A0.Raw, B0.Raw), _mm256_mul_pd(A1.Raw, B1.Raw));
        Destination = { _mm256_add_pd(Temp, _mm256_permute2f128_pd(Temp, Temp, 0x01)) };
    }

    inline void CrossProduct(const AVXF3& A, const AVXF3& B, AVXF3& Destination) {
        const __m128 Shuffled = _mm_sub_ps(
            _mm_mul_ps(A.Raw, _mm_shuffle_ps(B.Raw, B.Raw, _MM_SHUFFLE(3, 0, 2, 1))),
            _mm_mul_ps(B.Raw, _mm_shuffle_ps(A.Raw, A.Raw, _MM_SHUFFLE(3, 0, 2, 1))));
        Destination = { _mm_shuffle_ps(Shuffled, Shuffled, _MM_SHUFFLE(3, 0, 2, 1)) };
    }

    inline void LengthSquared(const AVXF3& Source, AVXF3& Destination) { DotProduct(Source, Source, Destination); }
    inline void LengthSquared(const AVXF4& Source, AVXF4& Destination) { DotProduct(Source, Source, Destination); }
    inline void LengthSquared(const AVXF8& Source, AVXF8& Destination) { DotProduct(Source, Source, Destination); }
    inline void LengthSquared(const AVXD4& Source, AVXD4& Destination) { DotProduct(Source, Source, Destination); }

    inline void Length(const AVXF3& Source, AVXF3& Destination) {
        DotProduct(Source, Source, Destination);
        SquareRoot(Destination, Destination);
    }
    inline void Length(const AVXF4& Source, AVXF4& Destination) {
        DotProduct(Source, Source, Destination);
        SquareRoot(Destination, Destination);
    }
    inline void Length(const AVXF8& Source, AVXF8& Destination) {
        DotProduct(Source, Source, Destination);
        SquareRoot(Destination, Destination);
    }
    inline void Length(const AVXD4& Source, AVXD4& Destination) {
        DotProduct(Source, Source, Destination);
        SquareRoot(Destination, Destination);
    }

    inline void Normalize(const AVXF3& Source, AVXF3& Destination) {
        AVXF3 Temp;
        Length(Source, Temp);
        Destination = Source / Temp;
    }
    inline void Normalize(const AVXF4& Source, AVXF4& Destination) {
        AVXF4 Temp;
        Length(Source, Temp);
        Destination = Source / Temp;
    }
    inline void Normalize(const AVXF8& Source, AVXF8& Destination) {
        AVXF8 Temp;
        Length(Source, Temp);
        Destination = Source / Temp;
    }
    inline void Normalize(const AVXD4& Source, AVXD4& Destination) {
        AVXD4 Temp;
        Length(Source, Temp);
        Destination = Source / Temp;
    }

    inline void DistanceSquared(const AVXF3& A, const AVXF3& B, AVXF3& Destination) { LengthSquared(A - B, Destination); }
    inline void DistanceSquared(const AVXF4& A, const AVXF4& B, AVXF4& Destination) { LengthSquared(A - B, Destination); }
    inline void DistanceSquared(const AVXF8& A, const AVXF8& B, AVXF8& Destination) { LengthSquared(A - B, Destination); }
    inline void DistanceSquared(const AVXD4& A, const AVXD4& B, AVXD4& Destination) { LengthSquared(A - B, Destination); }

    inline void Distance(const AVXF3& A, const AVXF3& B, AVXF3& Destination) { Length(A - B, Destination); }
    inline void Distance(const AVXF4& A, const AVXF4& B, AVXF4& Destination) { Length(A - B, Destination); }
    inline void Distance(const AVXF8& A, const AVXF8& B, AVXF8& Destination) { Length(A - B, Destination); }
    inline void Distance(const AVXD4& A, const AVXD4& B, AVXD4& Destination) { Length(A - B, Destination); }
    #pragma endregion
}