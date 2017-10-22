namespace mk
{
  template <typename ...Ts>
  struct tuple;

  template <typename T>
  struct tuple<T>
  {
    tuple(T value) : mValue(value) {}
    T mValue;
  };

  template <typename T, typename ...Ts>
  struct tuple<T, Ts...> : tuple<Ts...>
  {
    tuple(T value, Ts... args) : tuple<Ts...>(args...), mValue(value) {}
    T mValue;
  };

  template <typename ...Ts>
  tuple<Ts...> make_tuple(Ts&&... args)
  {
    return tuple<Ts...>(std::forward<Ts>(args)...);
  }

  template <int i, typename ...Ts>
  struct getImpl;

  template <int i, typename T, typename ...Ts>
  struct getImpl<i, T, Ts...>
  {
    static auto value(const tuple<T, Ts...>& tuple)
    {
      return getImpl<i - 1, Ts...>::value(tuple);
    }
  };
  
  template <typename ...Ts>
  struct getImpl<0, Ts...>
  {
    static auto value(const tuple<Ts...>& tuple)
    {
      return tuple.mValue;
    }
  };

  template <int i, typename ...Ts>
  auto get(const tuple<Ts...>& tuple)
  {
    return getImpl<i, Ts...>::value(tuple);
  }
}
