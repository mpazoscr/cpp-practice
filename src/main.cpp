#include <iostream>

#include "TypeTraits.hpp"
#include "Tuple.hpp"

struct TrivialStructType {};
class TrivialClassType {};
union TrivialUnionType{};
enum class EnumType {};
using FunctionType = int();
using ArrayType = int[];
using PointerType = char*;

// Poor testing but hey, this is for fun

static_assert(mk::is_void<void>::value, "");
static_assert(!mk::is_void<int>::value, "");
static_assert(!mk::is_void<TrivialStructType>::value, "");
static_assert(!mk::is_void<TrivialClassType>::value, "");
static_assert(!mk::is_void<TrivialUnionType>::value, "");
static_assert(!mk::is_void<EnumType>::value, "");
static_assert(!mk::is_void<FunctionType>::value, "");
static_assert(!mk::is_void<ArrayType>::value, "");
static_assert(!mk::is_void<PointerType>::value, "");

static_assert(mk::is_same<int, int>::value, "");
static_assert(mk::is_same<TrivialStructType, TrivialStructType>::value, "");
static_assert(mk::is_same<TrivialClassType, TrivialClassType>::value, "");
static_assert(mk::is_same<TrivialUnionType, TrivialUnionType>::value, "");
static_assert(mk::is_same<EnumType, EnumType>::value, "");
static_assert(mk::is_same<FunctionType, FunctionType>::value, "");
static_assert(mk::is_same<ArrayType, ArrayType>::value, "");
static_assert(mk::is_same<PointerType, PointerType>::value, "");

static_assert(!mk::is_same<int, float>::value, "");
static_assert(!mk::is_same<int, TrivialStructType>::value, "");
static_assert(!mk::is_same<int, TrivialClassType>::value, "");
static_assert(!mk::is_same<int, TrivialUnionType>::value, "");
static_assert(!mk::is_same<int, EnumType>::value, "");
static_assert(!mk::is_same<int, FunctionType>::value, "");
static_assert(!mk::is_same<int, ArrayType>::value, "");
static_assert(!mk::is_same<int, PointerType>::value, "");

static_assert(!mk::is_same<TrivialStructType, PointerType>::value, "");
static_assert(!mk::is_same<TrivialClassType, ArrayType>::value, "");
static_assert(!mk::is_same<TrivialUnionType, FunctionType>::value, "");
static_assert(!mk::is_same<EnumType, TrivialUnionType>::value, "");
static_assert(!mk::is_same<FunctionType, EnumType>::value, "");
static_assert(!mk::is_same<ArrayType, TrivialClassType>::value, "");
static_assert(!mk::is_same<PointerType, TrivialStructType>::value, "");

int main()
{
  auto tuple = mk::make_tuple(0, 1.0f, 'a', 'b');
  std::cout << mk::get<0>(tuple) << ", ";
  std::cout << mk::get<1>(tuple) << ", ";
  std::cout << mk::get<2>(tuple) << ", ";
  std::cout << mk::get<3>(tuple) << "\n\n";

  std::cout << "Press any key to finish...";
  std::cin.get();
}
