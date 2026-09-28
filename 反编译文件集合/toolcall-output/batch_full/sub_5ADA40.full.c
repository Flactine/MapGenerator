_DWORD *__thiscall sub_5ADA40(_DWORD *this, int a2, int a3)
{
  void *v5; // eax

  this[1] = 0;
  this[2] = a2;
  *(this + 12) = 1;
  *(this + 13) = 0;
  *this = &VectorClass<TRect<int>>::`vftable';
  if ( a2 )
  {
    if ( a3 )
    {
      this[1] = a3;
      return this;
    }
    v5 = operator new(16 * a2);
    if ( v5 )
    {
      this[1] = v5;
      *(this + 13) = 1;
      return this;
    }
    *(this + 13) = 1;
    this[1] = 0;
  }
  return this;
}
