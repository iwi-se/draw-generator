// urn.hpp by Ulrich Eisenecker, June 14, 2023

#ifndef URN_HPP
#define URN_HPP

#include <vector>
#include <iostream> // Because of cerr
#include <exception> 

namespace urn
{
   using uint = unsigned int;
   using Draw = std::vector<uint>;

   class UrnOR
   {
      public:
         explicit UrnOR(uint n,uint k,uint check = 1):m_n { n },
                                                      m_k { k },
                                                      m_balls(k,0)
         { 
            if (check == 1 && m_n == 0 && m_k > 0)
            {
               throw std::domain_error(
                          "UrnOR with n == 0 and k > 0 is not valid.");
            }
         }
         uint n() const
         {
            return m_n;
         }
         uint k() const
         {
            return m_k;
         }
         uint at(uint index) const
         {
            return m_balls.at(index);
         }
         uint operator[](uint index) const
         {
            return m_balls[index];
         }
         [[nodiscard]] virtual bool next()
         {
            for (uint down { m_k }; down > 0; --down)
            {
               if (m_balls[down - 1] < m_n - 1)
               {   
                  ++m_balls[down - 1];
                  for (uint up { down }; up < m_k; ++up)
                  {
                     m_balls[up] = 0;
                  }
                  return true;
               }
            }
            return false;
         }
         virtual ~UrnOR() = default;
      protected:
         const uint m_n,
                    m_k;
         Draw m_balls;
   };

   class UrnO: public virtual UrnOR
   {
      public:
         explicit UrnO(uint n,uint k,uint check = 2):UrnOR { n,k,check }
         { 
            if (check == 2 && m_k > m_n)
            {
               throw std::domain_error(
                          "UrnO with k > n is not valid.");
            }
            for (uint i { 1 }; i < m_k; ++i)
            {
               m_balls[i] = i;
            }
         }
         [[nodiscard]] bool next() override
         {
            while (UrnOR::next())
            {
               if (!repetitions())
               {
                  return true;
               };
            }
            return false;
         }
      protected:
         bool repetitions() const
         {
            for (uint i { 0 };i < m_k - 1; ++i)
            {
               for (uint j { i + 1 }; j < m_k; ++j)
               {
                  if (m_balls[i] == m_balls[j])
                  {
                     return true;
                  }
               }
            }
            return false;
         }
   };

   class UrnR: virtual public UrnOR
   {
      public:
         explicit UrnR(uint n,uint k,uint check = 3):UrnOR { n,k,check }
         { 
            if (check == 3 && m_n == 0)
            {
               throw std::domain_error(
                          "UrnR with n = 0 is not valid.");
            }
         }
         [[nodiscard]] bool next() override
         {
            while (UrnOR::next())
            {
               if (!unsorted())
               {
                  return true;
               };
            }
            return false;
         }
      protected:
         bool unsorted() const
         {
            for (uint i { 0 };i < m_k - 1; ++i)
            {
               if (m_balls[i] > m_balls[i + 1])
               {
                  return true;
               }
            }
            return false;
         }
   };
   
   class Urn: public UrnO, public UrnR
   {
      public: 
         explicit Urn(uint n,uint k):UrnOR { n,k },
                                     UrnO { n,k,1 },
                                     UrnR { n,k,1 }
         { 
            for (uint i { 1 }; i < m_k; ++i)
            {
               m_balls[i] = i;
            }
         }
         [[nodiscard]] bool next() override
         {
            while (UrnOR::next())
            {
               if (!unsorted() && !repetitions())
               {
                  return true;
               };
            }
            return false;
         }
   };

   //Fix start
   template <bool O, bool R>
   struct UrnSelector 
   {
      using UrnType = UrnOR;
   };

   template <>
   struct UrnSelector<true, false> 
   {
      using UrnType = UrnO;
   };

   template <>
   struct UrnSelector<false, true> 
   {
      using UrnType = UrnR;
   };

   template <>
   struct UrnSelector<false, false> 
   {
      using UrnType = Urn;
   };
   //Fix End

   template <typename T,bool ORDER = true,bool REPETITION = true>
   class GenericUrn
   {
      public:
         GenericUrn(uint k,const std::vector<T>& elements)
            :m_urn { static_cast<uint>(elements.size()),k },
             m_elements { elements }
         {}
         uint n() const
         {
            return m_urn.n();
         }
         uint k() const
         {
            return m_urn.k();
         }
         const T& at(uint index) const
         {
            return m_elements.at(m_urn.at(index));
         }
         const T& operator[](uint index) const
         {
            return m_elements[m_urn[index]];
         }
         [[nodiscard]] virtual bool next()
         {
            return m_urn.next();
         }
                 
      private:
         using UrnType = typename UrnSelector<ORDER,REPETITION>::UrnType;
         UrnType m_urn;
         std::vector<T> m_elements;
   };

   template <class T> // According to https://en.wikipedia.org/wiki/Permutation
   using Permutation = GenericUrn<T,true,true>;

   template <class T> // According to https://en.wikipedia.org/wiki/Partial_permutation
   using PartialPermutation = GenericUrn<T,true,false>;

   template <class T> // According to https://en.wikipedia.org/wiki/Combination
   using MultiCombination = GenericUrn<T,false,true>;

   template <class T> // According to https://en.wikipedia.org/wiki/Combination
   using Combination = GenericUrn<T,false,false>;

}
#endif // URN_HPP
