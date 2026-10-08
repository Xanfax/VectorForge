# VectorForge

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Version](https://img.shields.io/badge/version-0.3.0-green.svg)](#)
[![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](#)
[![ISA](https://img.shields.io/badge/ISA-AVX2%20%2B%20FMA3-orange.svg)](#)

Header-only AVX2 vector math library for C++. One header, no required dependencies.

```cpp
#include "VectorForge.hpp"

VFX::float8 Values;
Values <= 1.5f;                      // splat

VFX::AVXF8 Registers;
VFX::LoadAVX(Values, Registers);

VFX::AVXF8 Doubled = Registers * 2.0f;
VFX::StoreAVX(Doubled, Values);
```

---

## Requirements

| Compiler | Flags |
| :--- | :--- |
| MSVC | `/arch:AVX2` |
| GCC / Clang | `-mavx2 -mfma` |

> [!IMPORTANT]
> The header hard-errors at compile time if AVX2 and FMA3 are not enabled. There is no runtime dispatch and no scalar fallback — binaries built against it will not run on pre-Haswell hardware.

## Installation

Copy `VectorForge.hpp` into your include path. That's the whole install.

```cpp
#include "VectorForge.hpp"
using namespace VFX;   // optional
```

DirectXMath is optional. If it's on the include path, interop turns on automatically — see [DirectXMath interop](#directxmath-interop).

## Types

Everything lives in namespace `VFX`.

### Storage types

Plain memory, aligned where a register fills them.

| Float | Double | Integer |
| :--- | :--- | :--- |
| `float2` `float3` `float4` `float8` | `double2` `double3` `double4` | `int2` `int3` `int4` `int8` `int16` `int32` |

### Register types

One 128/256-bit register wrapped in a struct.

| Type | Register | Lanes | Pairs with |
| :--- | :--- | :--- | :--- |
| `AVXF3` | `__m128` | 3 × f32 | `float3` |
| `AVXF4` | `__m128` | 4 × f32 | `float4` |
| `AVXF8` | `__m256` | 8 × f32 | `float8` |
| `AVXD4` | `__m256d` | 4 × f64 | `double4` |
| `AVXI4` | `__m256i` | 4 × i64 | `int4` |
| `AVXI8` | `__m256i` | 8 × i32 | `int8` |
| `AVXI16` | `__m256i` | 16 × i16 | `int16` |
| `AVXI32` | `__m256i` | 32 × i8 | `int32` |

> [!NOTE]
> Integer types are named by **lane count**, not lane width. `AVXI8` is eight 32-bit lanes; `AVXI32` is thirty-two 8-bit lanes. A 256-bit integer register carries no lane width of its own, so the width lives in the type.

The underlying intrinsic is always reachable through `.Raw` for anything this header doesn't wrap.

### Moving between them

```cpp
LoadAVX(Source, Destination);     // storage -> register
StoreAVX(Source, Destination);    // register -> storage

Combine(Lower, Upper, Wide);      // two AVXF4 -> one AVXF8
Split(Wide, Lower, Upper);        // one AVXF8 -> two AVXF4
```

`LoadAVX` also builds a wide register directly from narrow storage types — two `float4`, four `float2`, or two `double2` into one `AVXF8`/`AVXD4`.

## API

<details>
<summary><b>Geometry</b></summary>

Available for both storage and register types.

`DotProduct` · `CrossProduct` · `Length` · `LengthSquared` · `Normalize` · `Distance` · `DistanceSquared` · `Lerp` · `Reflect`

`DualDot` computes two dot products in a single pass. Results interleave: even lanes hold `A0·B0`, odd lanes hold `A1·B1`.

Register-type `DotProduct` broadcasts its result to every lane rather than returning a scalar, so it feeds straight back into register arithmetic without a trip through a scalar register. This is what keeps `Normalize` a pure register operation.

</details>

<details>
<summary><b>Per-lane maths</b></summary>

`SquareRoot` · `Minimum` · `Maximum` · `UnsignedMinimum` · `UnsignedMaximum` · `AbsoluteValue` · `Negate` · `Floor` · `Ceiling` · `RoundNearest` · `Truncate` · `Clamp` · `Lerp`

</details>

<details>
<summary><b>Fused multiply-add</b></summary>

`MultiplyAdd` — computes `A * B + C` in one instruction, one rounding.

`MultiplySubtract` — computes `A * B - C`.

</details>

<details>
<summary><b>Approximations and reductions</b></summary>

`ReciprocalFast` · `ReciprocalSquareRootFast` — roughly 12 bits of precision.

`HorizontalSum` — collapses a register to a scalar. This is a reduction and costs accordingly; keep it out of inner loops.

</details>

## Conventions

- **Results go to an out-parameter**, not a return value.
  ```cpp
  Normalize(Source, Destination);
  ```

- **Nothing is comparable.** Every type deletes `==` `!=` `<` `>` `>=` `<=>`. None of them answer a yes/no question about a whole vector.

- **`<=` is the splat operator.** It fills every component with the given value. On register types it broadcasts to every lane.

- **Scalars are always the right operand.** The scalar overloads are members, so the vector has to be on the left. Enforced by the language, not by convention.

- **Operations with no hardware instruction are explicitly deleted**, not silently emulated. Calling one is a compile error naming the type:

  | Operation | Why |
  | :--- | :--- |
  | Integer divide, any width | No such instruction exists in any generation |
  | `AVXI4` multiply | 64-bit lane multiply needs AVX-512DQ |
  | `AVXI32` multiply | 8-bit lane multiply does not exist |
  | `AVXI4` min / max / abs | Needs AVX-512F + VL |

> [!WARNING]
> `AVXF3` leaves the `w` lane **unspecified**. `DotProduct` masks it off, but the arithmetic operators do not — garbage in `w` propagates through `+`, `-`, `*` and `/`. Zero it on load, or ignore it on read.

## DirectXMath interop

If `<DirectXMath.h>` is reachable on the include path, VectorForge includes it and defines `XMATH`. Nothing to configure — detection uses `__has_include` at compile time.

With it enabled, the float storage types convert to and from their DirectXMath counterparts by plain assignment:

| VectorForge | DirectXMath |
| :--- | :--- |
| `float2` | `DirectX::XMFLOAT2` |
| `float3` | `DirectX::XMFLOAT3` |
| `float4` | `DirectX::XMFLOAT4` |

```cpp
DirectX::XMFLOAT3 Position = { 1.f, 2.f, 3.f };

VFX::float3 Local = Position;    // XMFLOAT3 -> float3
Position = Local;                // float3 -> XMFLOAT3
```

- **Conversion only.** No DirectXMath operators are added, and `XMVECTOR` is not wrapped — go through `XMLoadFloat3` / `XMStoreFloat3` on the DirectXMath side as usual.
- **Storage types only.** Register types (`AVXF3`, `AVXF4`, …) have no DirectXMath conversions; load from the storage type.
- **Mixed arithmetic follows the left-operand rule.** `Local + Position` compiles, because `Position` converts to `float3`. `Position + Local` does not, because conversions are never applied to the left-hand object of a member operator.

> [!NOTE]
> Detection checks that the header *exists*, not that you want it. Every translation unit that includes VectorForge on a machine with the Windows SDK pays the cost of parsing DirectXMath.

## License

GPL-3.0-only. See [the header](VectorForge.hpp) for the full notice.

The copyright holder reserves the right to license VectorForge under separate commercial terms. No commercial license is granted except by written agreement.

Copyright © 2026 StellarWorks/Xada Engine
