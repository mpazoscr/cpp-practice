namespace mk
{
  template <typename T, T v>
  struct integral_constant
  {
    using value_type = T;
    using type = integral_constant<T, v>;

    constexpr T operator()() const noexcept { return value; }
    constexpr operator T() const noexcept { return value; }
   
    static constexpr T value = v;
  };

  template <bool v>
  using bool_constant = integral_constant<bool, v>;

  using false_type = bool_constant<false>;
  using true_type = bool_constant<true>;

  template <typename T>
  struct is_void : false_type {};

  template <>
  struct is_void<void> : true_type {};

  template <typename T, typename U>
  struct is_same : false_type {};

  template <typename T>
  struct is_same<T, T> : true_type {};
}
