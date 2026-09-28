void __thiscall sub_59AFA0(int *this)
{
  int *this_1; // edi
  int p_MapCoords_1; // eax
  double v3; // st7
  int Y_1; // ebx
  CellClass *i; // eax
  int n400; // eax
  int n50000; // edi
  CellClass *j; // ecx
  __int64 v9; // rax
  int n50000_1; // esi
  CellStruct MapCoords; // [esp+10h] [ebp-48h]
  int v12; // [esp+14h] [ebp-44h]
  int n100; // [esp+18h] [ebp-40h]
  int p_MapCoords; // [esp+1Ch] [ebp-3Ch] BYREF
  int *this_2; // [esp+20h] [ebp-38h]
  int n400_1; // [esp+24h] [ebp-34h]
  int p_n2; // [esp+28h] [ebp-30h] BYREF
  int Y; // [esp+2Ch] [ebp-2Ch]
  double v19; // [esp+30h] [ebp-28h]
  double v20; // [esp+38h] [ebp-20h]
  double p_MapCoords_2; // [esp+40h] [ebp-18h]
  int v22[4]; // [esp+48h] [ebp-10h] BYREF

  this_1 = this; /*0x59afad*/
  this_2 = this; /*0x59afaf*/
  this[194] = 1; /*0x59afb3*/
  p_MapCoords_1 = sub_42B1F0(); /*0x59afbd*/
  v3 = this_1[19]; /*0x59afc2*/
  p_MapCoords = p_MapCoords_1; /*0x59afc5*/
  v12 = 0; /*0x59afcb*/
  n100 = 0; /*0x59afcf*/
  v19 = 0.0; /*0x59afd9*/
  v20 = (1.0 - v3 * 0.01) * (0.5 - 0.45) + 0.45; /*0x59affb*/
  p_MapCoords_2 = p_MapCoords_1; /*0x59b003*/
  n400_1 = Game::F2I64(p_MapCoords_2 * 0.03 * v20); /*0x59b016*/
  Y_1 = MouseClass::Instance.MapRect.Height / 2 + MouseClass::Instance.MapRect.Width / 2; /*0x59b030*/
  Y = Y_1; /*0x59b038*/
  p_n2 = Y_1 + 1; /*0x59b03f*/
  sub_578350(&MouseClass::Instance); /*0x59b043*/
  for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59b054*/
  {
    p_MapCoords = i->MapCoords; /*0x59b059*/
    *(dword_ABED10 + 20 * p_MapCoords + 20 * dword_89C2DC * SHIWORD(p_MapCoords) + 15) = 0; /*0x59b07a*/
  }
  v22[0] = MouseClass::Instance.VisibleRect.X + 1; /*0x59b0af*/
  v22[1] = MouseClass::Instance.VisibleRect.Y + 1; /*0x59b0bb*/
  v22[2] = MouseClass::Instance.VisibleRect.Width - 2; /*0x59b0c2*/
  v22[3] = MouseClass::Instance.VisibleRect.Height - 2; /*0x59b0c6*/
  if ( v20 > 0.0 ) /*0x59b0ca*/
  {
    while ( n100 < 100 ) /*0x59b0db*/
    {
      n400 = Game::F2I64((v20 - v19) * p_MapCoords_2); /*0x59b0ed*/
      if ( n400 >= n400_1 ) /*0x59b0f8*/
        n400 = n400_1; /*0x59b0fa*/
      LOWORD(p_MapCoords) = Y_1 + 1; /*0x59b119*/
      HIWORD(p_MapCoords) = Y_1; /*0x59b11e*/
      v12 += sub_59BBC0(this_1, n400, v22, &p_n2, 1, &p_MapCoords, 0.75, 1); /*0x59b133*/
      ++n100; /*0x59b137*/
      n50000 = 50000; /*0x59b144*/
      MapCoords = 0; /*0x59b149*/
      v19 = v12 / p_MapCoords_2; /*0x59b15b*/
      sub_578350(&MouseClass::Instance); /*0x59b15f*/
      for ( j = MapClass::CellIteratorNext(&MouseClass::Instance); j; j = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59b172*/
      {
        if ( !*(dword_ABED10 + 20 * j->MapCoords.X + 20 * dword_89C2DC * j->MapCoords.Y + 15) ) /*0x59b191*/
        {
          v9 = j->MapCoords.X - (Y_1 + 1); /*0x59b1ac*/
          n50000_1 = (HIDWORD(v9) ^ v9) - HIDWORD(v9) + abs32(j->MapCoords.Y - Y_1); /*0x59b1b1*/
          if ( n50000_1 < n50000 ) /*0x59b1b5*/
          {
            n50000 = n50000_1; /*0x59b1ba*/
            MapCoords = j->MapCoords; /*0x59b1bc*/
          }
        }
      }
      p_n2 = MapCoords.X; /*0x59b1e2*/
      Y = MapCoords.Y; /*0x59b1e6*/
      if ( v19 >= v20 ) /*0x59b1ef*/
        break; /*0x59b1ef*/
      this_1 = this_2; /*0x59b0d2*/
    }
  }
}
