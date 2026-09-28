Random *__thiscall Randomizer::Random(Random *this)
{
  Random *result; // eax
  int n250; // edx
  int n250_1; // esi

  if ( *this ) /*0x65c780*/
    return 0; /*0x65c785*/
  *(this + *(this + 1) + 3) ^= *(this + *(this + 2) + 3); /*0x65c79d*/
  n250 = *(this + 1); /*0x65c79f*/
  result = *(this + n250++ + 3); /*0x65c7a5*/
  n250_1 = *(this + 2) + 1; /*0x65c7aa*/
  *(this + 1) = n250; /*0x65c7b1*/
  *(this + 2) = n250_1; /*0x65c7b4*/
  if ( n250 >= 250 ) /*0x65c7b7*/
    *(this + 1) = 0; /*0x65c7b9*/
  if ( n250_1 >= 250 ) /*0x65c7c7*/
    *(this + 2) = 0; /*0x65c7c9*/
  return result; /*0x65c787*/
}
