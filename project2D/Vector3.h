#pragma once
struct Vector3
{
	Vector3();
	Vector3(float x, float y, float z);

	//---------------------------------------
	// MAGNITUDE	   https://bit.ly/1CcLWZV
	//---------------------------------------
	//			 /----↑
	//			/	  |
	//		   /      |-→ Magnitude
	//	      /		  |
	//		 / -------↓
	//
	// The length from start to end of vector.
	//---------------------------------------

	float magnitude();
	float magnitudeSqr();

	//---------------------------------------
	// NORMALISE	   https://bit.ly/2WFsHUY
	//---------------------------------------
	//			  /
	//			 /	Div: 1.6   /
	// Mag = 5  /   -------→  /  Mag = 3
	//	       /		     /
	//		  / 
	//
	// Normalizing is the process of shrinking or
	// increasing a vectors length while keeping it
	// facing the same direction and keeping all components
	// reletive to thier previous size. 
	//---------------------------------------

	void normalise();

	//---------------------------------------
	// DOT			   https://bit.ly/2icFWN8
	//---------------------------------------
	//
	//	     \     /			
	//		  \~~~/	  Dot = ~45
	//		   \ /	 			
	//			V		
	//
	// The cosine of the angle between two vectors.
	//---------------------------------------

	float dot(const Vector3& rhs);

	//---------------------------------------
	// CROSS		   https://bit.ly/227tUCl
	//---------------------------------------
	//
	//	    |
	//	    | ←- A * B = C
	//	    |
	//	    |_________ ←- B    C.Mag = Area
	//	     \        ﹨
	//   A -→ \	 Area  ﹨
	//         \ - - - -﹨
	//
	// The cross is the product of vectors A * B
	// being another vector that is postioned at
	// a right angle from a and b. 
	//---------------------------------------

	Vector3 cross(const Vector3& rhs);

	//---------------------------------------
	// ARITHMETIC	   https://bit.ly/1CcLWZV
	//---------------------------------------
	//
	//		ADD:	Add two vectors
	//		x1 + x2 = x1
	//		y1 + y2 = y1
	//		z1 + z2 = z1
	//
	//		SUB:	Sub two Vectors
	//		x1 - x2 = x1
	//		y1 - y2 = y1
	//		z1 - z2 = z1
	//		
	//		MULTI:	Multiply two vectors
	//		x1 * x2 = x1
	//		y1 * y2 = y1
	//		z1 * z2 = z1
	//
	//		DIV:	Divide two vectors
	//		x1 / x2 = x1
	//		y1 / y2 = y1
	//		z1 / z2 = z1
	//
	//---------------------------------------

	// OPERATORS					  
	Vector3 operator+(const Vector3& rhs);		//Add two vectors
	Vector3 operator-(const Vector3& rhs);		//Sub two vectors
	Vector3 operator*(const float rhs);			//Multi
	Vector3 operator/(const float rhs);			//Div

	// EQUALS OPERATORS
	Vector3& operator+=(const Vector3& rhs);	//Add other to this
	Vector3& operator-=(const Vector3& rhs);	//Sub other to this
	Vector3& operator*=(const float rhs);		//Multiply with value
	Vector3& operator/=(const float rhs);		//Divide with value

	//---------------------------------------
	// SUBSCRIPT
	//---------------------------------------
	//
	//	 Pos[0] ← X	 Pos[1] ← Y	 Pos[2] ← Z
	//
	// Used to access x, y and z using subscript.
	//---------------------------------------

	float& operator[](int index);

	//---------------------------------------
	// FLOAT OPERATOR
	//---------------------------------------
	//
	//		X →	Pos[0] = 3.0f
	//		Y →	Pos[1] = 7.0f
	//		Z →	Pos[2] = 2.0f
	//
	// Used to assign postion using a subscript with a float.
	//---------------------------------------

	operator float*();

	//---------------------------------------
	// POSTION		   https://bit.ly/1CcLWZV
	//---------------------------------------
	//
	//	 	 y   z 
	//	     |  / * ← (x = 4, y = 3, z = 3)
	//	     | /
	//	 	 |/
	// x ----+----* ← (x = 4, y = 0, z = 0)
	//	    /|
	//     / |	  + ← (x = 0, y = 0, z = 0)
	//    /  |
	//
	// Vectors postion
	//---------------------------------------

	float x;
	float y;
	float z;
};

// Multiply float with Vector
Vector3 operator*(float lhs, Vector3 rhs);