#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include<functional>
#include<exception>
#include<iostream>

namespace cs540{

class BadFunctionCall{};

template <typename RType, typename...ArgTypes>
class Abstract{
public:
  virtual ~Abstract(){}
  virtual Abstract *clone() const =0;
  virtual RType operator()(ArgTypes...args)=0;
};

template <typename RType, typename F, typename...ArgTypes>
class Implim: public Abstract<RType, ArgTypes...>{
public:

  F func;

  Implim(){}

  ~Implim(){}

  Implim(F fnct):func(fnct){}

  Implim<RType, F, ArgTypes...> *clone() const{
    Implim *i;
    try{
      i= new Implim(func);
    }
    catch(const std::bad_alloc &e){
      std::cout<<e.what()<<"\n";
      i=nullptr;
    }
    return i;
  }

  RType operator()(ArgTypes...args){
    return func(args...);
  }

};


template<typename T> class Function;

template<typename RType, typename...ArgTypes>
class Function<RType(ArgTypes...)>{
public:
  Abstract<RType, ArgTypes...> *abs;

  Function():abs(nullptr){}
  
  template<typename FType>
  Function(FType f){
    try{
      this->abs= new Implim<RType, FType, ArgTypes...>(f);
    }
    catch(const std::bad_alloc &e){
      std::cout<<e.what()<<"\n";
      this->abs=nullptr;
    }
  }
  
  Function(const Function &f){
    this->abs=f.abs->clone();
  }
  
  Function& operator=(const Function &f){
    if(this->abs!=f.abs){
      if(this->abs!=nullptr)
        delete this->abs;
        
      this->abs=f.abs->clone();
    }
  }
  
  ~Function(){
    delete abs;
  }
  
  RType operator()(ArgTypes...args){
    if(this->abs==nullptr)
      throw BadFunctionCall();
      
    return (*abs)(args...);
  }
  
  explicit operator bool() const{
    if(this->abs!=nullptr)
      return true;
    
    return false;
  }
  
  friend bool operator==(const Function<RType(ArgTypes...)> &f, std::nullptr_t){
    return !f;
  }
  
  friend bool operator==(std::nullptr_t, const Function<RType(ArgTypes...)> &f){
    return !f;
  }
  
  friend bool operator!=(const Function<RType(ArgTypes...)> &f, std::nullptr_t){
    return bool(f);
  }
  
  friend bool operator!=(std::nullptr_t, const Function<RType(ArgTypes...)> &f){
    return bool(f);
  }

};

}  //namespace

#endif  //FUNCTION_HPP_