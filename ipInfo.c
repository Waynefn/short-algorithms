char* int2ip(int a) {
	unsigned char segs[4];
	char* buf = new char[16];
	for (int i =3; i >=0; i--)
		segs[3-i] = (a >> (8 * i))&255;
	sprintf(buf, "%3u.%3u.%3u.%3u", segs[0], segs[1], segs[2], segs[3]);
	return buf;
}

int ip2int(char * a) {
	int buf[4];
	sscanf(a, "%d.%d.%d.%d", &buf[0], &buf[1], &buf[2], &buf[3]);
	return (buf[0]<<24)+(buf[1]<<16)+(buf[2]<<8)+buf[3];
}

void IPinfo(char *a, int cidr) {
	int ip = ip2int(a);
	int hostmask = (1 << 32 - cidr) - 1;
	int netmask = ~hostmask;
	int nid = ip & netmask;
	int broad =( ip&netmask) | hostmask;

	printf("IP addr.   : %s/%d\n", int2ip(ip),cidr);
	printf("Network ID : %s\n", int2ip(nid));
	printf("Mask       : %s\n", int2ip(netmask));
	printf("Broadcast  : %s\n", int2ip(broad));
	printf("Host Range : %s ~ %s\n", int2ip(nid+1), int2ip(broad-1));
	printf("Host Num.  : %d (2^%d-2)\n",(1<<(32-cidr))-2, 32 - cidr);
}



// IPinfo("11.50.100.3", 10);
