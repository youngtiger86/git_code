int main(int argc, const char * argv[]){
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc]init];
	NSLog(@¨Hello, world\n¨);
	[pool drain];
	return 0;
}