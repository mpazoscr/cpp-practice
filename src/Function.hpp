#ifndef MK_FUNCTION_HPP
#define MK_FUNCTION_HPP

#include <array>
#include <string>
#include <exception>

namespace mk
{
  class bad_function_call : public std::exception
  {
  public:
    bad_function_call() noexcept
    : mMessage{"badfunctioncall"}
    {
    }

    const char* what() const override
    {
      return mMessage.data();
    }

  private:
    const std::string mMessage;
  };

  template <typename Ret, typename ...Args>
  class FunctionImplInterface
  {
  public:
    virtual ~FunctionImplInterface()
    {
    }

    virtual Ret call(Args&&... args) = 0;
  };

  template <typename Callable, typename Ret, typename ...Args>
  class FunctionImpl : FunctionImplInterface<Ret, Args...>
  {
  public:
    FunctionImpl(Callable&& callable) noexcept
    : mCallable(callable)
    {
    }

    virtual ~FunctionImpl()
    {
    }

    Ret call(Args&&... args) override
    {
      return mCallable(std::forward<Args>(args)...);
    }

  private:
    Callable mCallable;
  };

  template <typename T>
  class function;

  template <typename Ret, typename ...Args>
  class function<Ret(Args...)>
  {
  public:
    function() noexcept
    : mImpl{}
    {
    }

    template <typename Callable>
    function(Callable&& callable) noexcept
    : mImpl{}
    {
      // Make sure the buffer is enough to contain Callable
      static_assert(sizeof(PointerBuffer) >= sizeof(FunctionImpl<Callable, Ret, Args...>), "Function storage insufficient");

      // Type erasure
      new (getImpl()) FunctionImpl<Callable, Ret, Args...>(std::forward<Callable>(callable));
    }

    ~function()
    {
      if (isInitialised())
      {
        getImpl()->~FunctionImplInterface();
      }
    }

    Ret operator()(Args&&... args)
    {
      checkInitialised();
      return getImpl()->call(std::forward<Args>(args)...);
    }

    explicit operator bool() noexcept
    {
      return isInitialised();
    }

    // Missing move and copy ctor and operator assignment

  private:
    bool isInitialised()
    {
      return mImpl != PointerBuffer();
    }

    void checkInitialised()
    {
      // Zero initialised
      if (!isInitialised())
      {
        throw bad_function_call();
      }
    }
    
    void* rawBuffer()
    {
      return static_cast<void*>(mImpl.data());
    }

    FunctionImplInterface<Ret, Args...>* getImpl()
    {
      return static_cast<FunctionImplInterface<Ret, Args...>*>(rawBuffer());
    }

  private:
    // Small buffer optimisation (SBO)
    // This assumes pointers to functions will not occupy more than 32 chars (at least 32 bytes). Potentially risky
    // as different compilers can require different sizes depending on their implementation of, for instance, virtual
    // member functions of classes with virtual inheritance. Hence the assertion in the constructor.
    using PointerBuffer = std::array<char, 32>;
    alignas (std::intptr_t) PointerBuffer mImpl;
  };
}

#endif // MK_FUNCTION_HPP
