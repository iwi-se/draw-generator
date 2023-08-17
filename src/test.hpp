template <typename T,bool ORDER = true,bool REPETITION = true>
class GenericUrn
{
template <bool O,bool R>
         class SelectUrn
         {
            public:
               using UrnType = UrnOR;
         };
         template <>
         class SelectUrn<true,false>
         {
            public:
               using UrnType = UrnO;
         };
         template <>
         class SelectUrn<false,true>
         {
            public:
               using UrnType = UrnR;
         };
         template <>
         class SelectUrn<false,false>
         {
            public:
               using UrnType = Urn;
         };
         using UrnType = typename SelectUrn<ORDER,REPETITION>::UrnType;
         UrnType m_urn;
};