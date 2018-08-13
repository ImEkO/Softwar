int  gestion_erreur(int argc, char** argv, char c)
{
  char* strg;
  int (*tab[5]) ();
  int i;

  i = 0;
  if (argc){}
  if (argv){}
  strg = "darlA";
  tab[0] = &ls_d;
  tab[1] = &ls_a;
  tab[2] = &ls_r;
  tab[3] = &ls_l;
  tab[4] = &ls_A;
  while ( strg[i] != '\0' )
    {
      if (c == strg[i])
        (*tab[i])();
          i++;
      }
  my_putstr("\n");
  return (0);
}
