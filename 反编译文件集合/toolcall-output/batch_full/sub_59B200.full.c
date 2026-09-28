int __thiscall sub_59B200(int *this)
{
  CellClass *i; // eax
  int v3; // esi
  double v4; // st7
  int n400; // eax
  int v6; // edi
  int n50000; // ebp
  int v8; // ebx
  __int16 *v9; // esi
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // eax
  __int64 v14; // rax
  int n50000_1; // eax
  bool v16; // zf
  int result; // eax
  int v18; // [esp+10h] [ebp-B8h]
  int n2; // [esp+10h] [ebp-B8h]
  int p_n2_2; // [esp+14h] [ebp-B4h]
  double v21; // [esp+18h] [ebp-B0h]
  int v22; // [esp+20h] [ebp-A8h]
  int n100; // [esp+24h] [ebp-A4h]
  int v24; // [esp+28h] [ebp-A0h]
  int *v25; // [esp+2Ch] [ebp-9Ch]
  int v26; // [esp+30h] [ebp-98h] BYREF
  int v27; // [esp+34h] [ebp-94h]
  int v28; // [esp+38h] [ebp-90h]
  int v29; // [esp+3Ch] [ebp-8Ch]
  double v30; // [esp+40h] [ebp-88h]
  int p_MapCoords; // [esp+4Ch] [ebp-7Ch] BYREF
  int p_n2_1; // [esp+50h] [ebp-78h]
  int v33; // [esp+54h] [ebp-74h]
  int v34; // [esp+58h] [ebp-70h]
  int *this_1; // [esp+5Ch] [ebp-6Ch]
  int p_n2; // [esp+60h] [ebp-68h] BYREF
  int v37; // [esp+64h] [ebp-64h]
  double v38; // [esp+68h] [ebp-60h]
  double v39; // [esp+70h] [ebp-58h]
  _DWORD v40[2]; // [esp+78h] [ebp-50h] BYREF
  int Width; // [esp+80h] [ebp-48h]
  int Height; // [esp+84h] [ebp-44h]
  int X; // [esp+88h] [ebp-40h]
  int Y; // [esp+8Ch] [ebp-3Ch]
  int Width_1; // [esp+90h] [ebp-38h]
  int Height_1; // [esp+94h] [ebp-34h]
  int v47; // [esp+98h] [ebp-30h]
  int n400_1; // [esp+9Ch] [ebp-2Ch]
  double v49; // [esp+A0h] [ebp-28h]
  double v50; // [esp+A8h] [ebp-20h]
  int v51; // [esp+B4h] [ebp-14h]
  double v52; // [esp+B8h] [ebp-10h]
  double v53; // [esp+C0h] [ebp-8h]

  this_1 = this;
  this[194] = 1;
  v18 = sub_42B1F0();
  n100 = 0;
  v38 = (1.0 - this[19] * 0.01) * (0.2 - 0.15) + 0.15;
  v50 = v18;
  n400_1 = Game::F2I64(v50 * 0.06 * v38);
  sub_578350(&MouseClass::Instance);
  for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) )
    *(dword_ABED10 + 20 * *&i->MapCoords + 20 * dword_89C2DC * HIWORD(*&i->MapCoords) + 15) = 0;
  *&v30 = Randomizer::Random(&dst_);
  v40[0] = MouseClass::Instance.VisibleRect.X;
  v40[1] = MouseClass::Instance.VisibleRect.Y;
  if ( *&v30 * 2.328306437080797e-10 >= 0.5 )
  {
    Width = MouseClass::Instance.VisibleRect.Width;
    Height = MouseClass::Instance.VisibleRect.Height / 2 - 1;
    X = MouseClass::Instance.VisibleRect.X;
    Y = MouseClass::Instance.VisibleRect.Height / 2 + MouseClass::Instance.VisibleRect.Y + 1;
    Width_1 = MouseClass::Instance.VisibleRect.Width;
    Height_1 = Height;
  }
  else
  {
    Height = MouseClass::Instance.VisibleRect.Height;
    Width = MouseClass::Instance.VisibleRect.Width / 2 - 1;
    X = MouseClass::Instance.VisibleRect.Width / 2 + MouseClass::Instance.VisibleRect.X + 1;
    Y = MouseClass::Instance.VisibleRect.Y;
    Width_1 = Width;
    Height_1 = MouseClass::Instance.VisibleRect.Height;
  }
  n2 = 2;
  v25 = v40;
  do
  {
    v22 = 0;
    v39 = 0.0;
    v26 = *v25;
    v27 = v25[1];
    v28 = v25[2];
    v29 = v25[3];
    v3 = v27 + MouseClass::Instance.MapRect.Width + v29 / 2 - v28 / 2 - v26;
    p_n2_1 = v26 + v29 / 2 + v28 / 2 + v27 + 1;
    v33 = v3;
    p_n2 = p_n2_1;
    v37 = v3;
    if ( v29 <= v28 )
    {
      v4 = v28;
      v30 = 1.0;
      v21 = v29;
      v49 = v4 / v21 * 1.2;
    }
    else
    {
      v49 = 1.0;
      v21 = v29;
      v4 = v28;
      v30 = v21 / v4 * 1.2;
    }
    v53 = 1.0 / (v4 * 0.5 * (v4 * 0.5));
    v52 = 1.0 / (v21 * 0.5 * (v21 * 0.5));
    if ( v38 > 0.0 )
    {
      do
      {
        if ( n100 >= 100 )
          break;
        n400 = Game::F2I64((v38 - v39) * v50);
        if ( n400 >= n400_1 )
          n400 = n400_1;
        LOWORD(p_MapCoords) = p_n2_1;
        HIWORD(p_MapCoords) = v3;
        v22 += sub_59BBC0(this_1, n400, &v26, &p_n2, 1, &p_MapCoords, 0.75, 1);
        p_n2_2 = 0;
        ++n100;
        v6 = 2 * v26 - MouseClass::Instance.MapRect.Width + 1;
        n50000 = 50000;
        v47 = v6 + 2 * v28 + 2;
        v8 = MouseClass::Instance.MapRect.Width + 2 * v27 + 1;
        v51 = v8 + 2 * v29 + 2;
        v39 = v22 / v50;
        if ( dword_89C2DC * dword_89C2DC > 0 )
        {
          v24 = 0;
          v34 = dword_89C2DC * dword_89C2DC;
          do
          {
            v9 = (dword_ABED10 + v24);
            v10 = *(dword_ABED10 + v24 + 2);
            v11 = *(dword_ABED10 + v24);
            v12 = v11 + v10;
            v13 = v11 - v10;
            if ( v12 >= v8
              && v12 <= v51
              && v13 >= v6
              && v13 <= v47
              && !*(v9 + 15)
              && sub_59BAB0((dword_ABED10 + v24), &v26, 1, v53, v52) )
            {
              v14 = v9[1] - v33;
              n50000_1 = Game::F2I64(((HIDWORD(v14) ^ v14) - HIDWORD(v14)) * v49 + abs32(*v9 - p_n2_1) * v30);
              if ( n50000_1 < n50000 )
              {
                n50000 = n50000_1;
                p_n2_2 = *v9;
              }
            }
            v16 = v34 == 1;
            v24 += 80;
            --v34;
          }
          while ( !v16 );
          LOWORD(v3) = v33;
        }
        p_n2 = p_n2_2;
        v37 = SHIWORD(p_n2_2);
      }
      while ( v39 < v38 );
    }
    result = n2 - 1;
    v16 = n2 == 1;
    v25 += 4;
    --n2;
  }
  while ( !v16 );
  return result;
}
