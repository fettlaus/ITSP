void endianTest(int *endian_ness)
{
	if((*(unsigned short *) ("#S") >> 8) == '#')
	{
		/* printf("Big endian = no change\n"); */
		*endian_ness = !(0);
	}
	else
	{
		/* printf("Little endian = swap\n"); */
		*endian_ness = 0;
	}
}
