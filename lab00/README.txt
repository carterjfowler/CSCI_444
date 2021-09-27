Carter Fowler

1. Int + float + char

2. 
	Integer Component: offset is 0, length is sizeof(int)
	Float Component: offset is sizeof(int), length is sizeof(float)
	Char Component: offset is sizeof(int) + sizeof(float), length is sizeof(char)

3.
	Integer Component: offset is sizeof(int), length is sizeof(int)
	Float Component: offset is dataSize * sizeof(int) + sizeof(float), length is sizeof(float)
	Char Component: offset is dataSize * (sizeof(int) + sizeof(float)) + sizeof(char), length is sizeof(char) 

4. When you need all the data for a single vector very easily

5. When you want to work with the different data separately (i.e. only the integers, in this situation)