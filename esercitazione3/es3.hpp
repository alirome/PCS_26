#pragma once
#include <concepts>
#include <iostream>
#include <numeric>

//il programma non gestisce i segni negativi degli infiniti 


template<typename I> 
class rational{
    I num_;
    I den_;
    bool Inf;
    bool NaN;

    void semplifica(){
        if (NaN || Inf){
            return;
        }
        if (num_==0){
            den_= 1;
            return;
        }
        I multiplo= std::gcd(num_, den_);
        num_ /= multiplo;
        den_ /= multiplo;
    }
    
public:
    //inizializzo
    rational()
        : num_(0.0), den_(1.0), Inf(false), NaN(false)
    {}
    // user-defined
    rational(const I& pn, const I& pd)
        : num_(pn), den_(pd), Inf(false), NaN(false)
        {
            if (den_==0 && num_!=0){ 
                Inf = true;
            }
            if (den_==0 && num_==0){
                NaN = true;
            }     
            else{
                semplifica();
            }
        }
    I num() const {return num_;}
    I den() const {return den_;}
    bool isInf() const {return Inf;}
    bool isNaN() const {return NaN;}

    rational& operator+= (const rational& other){
        if (this->isNaN() ||other.isNaN()){ // forse ci vuole NaN
            num_=0; 
            den_=0;
            Inf= false;
            NaN= true;
            return *this;
        }
        
        if (this->isInf() ||other.isInf()){
            num_=1; 
            den_=0;
            Inf= true;
            NaN= false;
            return *this;
        }
        // calcolo somma
        num_= (num_ * other.den_)+ (other.num_ * den_);
        den_= (den_ * other.den_);
        semplifica();
        return *this;
    }

    rational operator+ (const rational& other) const {
        rational ret= *this;
        ret += other;
        return ret;
    }

    rational& operator-= (const rational& other) {
        if (this->isNaN() ||other.isNaN()){
            num_=0; 
            den_=0;
            Inf= false;
            NaN= true;
            return *this;
        }
        
        if (this->isInf() ||other.isInf()){
            num_=1; 
            den_=0;
            Inf= true;
            NaN= false;
            return *this;
        }

        num_= (num_ * other.den_)- (other.num_ * den_);
        den_= (den_ * other.den_);
        semplifica();
        return *this;
    }

    rational operator- (const rational& other) const{
        rational ret= *this;
        ret -= other;
        return ret;
    }

    rational& operator*= (const rational& other) {
        if (this->isNaN() ||other.isNaN()){
            num_=0; 
            den_=0;
            Inf= false;
            NaN= true;
            return *this;
        }
        
        if (this->isInf() ||other.isInf()){
            num_=1; 
            den_=0;
            Inf= true;
            NaN= false;
            return *this;
        }

        num_= (num_ * other.num_);
        den_= (den_ * other.den_);
        semplifica();
        return *this;
        
    }

    rational operator* (const rational& other) const {
        rational ret= *this;
        ret *= other;
        return ret;
    }

    rational& operator/= (const rational& other) {
        if (this->isNaN() ||other.isNaN()){
            num_=0; 
            den_=0;
            Inf= false;
            NaN= true;
            return *this;
        }
        
        if (this->isInf() ||other.isInf()){
            num_=1; 
            den_=0;
            Inf= true;
            NaN= false;
            return *this;
        }

        num_= (num_ * other.den_);
        den_= (den_ * other.num_);
        
        semplifica();
        return *this;
        
    }

    rational operator/ (const rational& other)const {
        rational ret= *this;
        ret /= other;
        return ret;
    } 

};

template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& f)
{
    if (f.isNaN()) {
        os<< "NaN";
        return os;
    }
    if (f.isInf()) {
        os<< "Inf";
        return os;
    }
    else {
        os<< f.num() << '/' << f.den();
        return os;
    }
}