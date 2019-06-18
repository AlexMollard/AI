#pragma once
struct Vector2
{
	//Constructors
	Vector2();
	Vector2(const float x, const float y);

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

	float dot(const Vector2& rhs);

	//---------------------------------------
	// DIRECTION	   
	//---------------------------------------
	//		
	//		 | ← Right
	//		 | 
	//	     |-------→ Vector
	//		 | 
	//		 | ← Left
	//
	// Get 90 degrees right or left of vector.
	//---------------------------------------

	Vector2 right();
	Vector2 left();

	//---------------------------------------
	// ARITHMETIC	   https://bit.ly/1CcLWZV
	//---------------------------------------
	//
	//		ADD:	Add two vectors
	//	    x1 + x2 = x1
	//		y1 + y2 = y1
	//
	//		SUB:	Sub two Vectors
	//		x1 - x2 = x1
	//		y1 - y2 = y1
	//		
	//		MULTI:	Multiply two vectors
	//		x1 * x2 = x1
	//		y1 * y2 = y1
	//
	//		DIV:	Divide two vectors
	//		x1 / x2 = x1
	//		y1 / y2 = y1
	//
	//---------------------------------------

	// OPERATORS
	Vector2 operator+(const Vector2& rhs);		//Add two vectors
	Vector2 operator-(const Vector2& rhs);		//Sub two vectors
	Vector2 operator*(const float rhs);			//Multi
	Vector2 operator/(const float rhs);			//Div

	// EQUALS OPERATORS
	Vector2& operator+=(const Vector2& rhs);	//Add other to this
	Vector2& operator-=(const Vector2& rhs);	//Sub other to this
	Vector2& operator*=(const float rhs);		//Multiply with value
	Vector2& operator/=(const float rhs);		//Divide with value

	//---------------------------------------
	// SUBSCRIPT
	//---------------------------------------
	//
	//		Pos[0] ← X		Pos[1] ← Y
	//
	// Used to access x and y using subscript.
	//---------------------------------------

	float& operator[](int index);

	//---------------------------------------
	// FLOAT OPERATOR
	//---------------------------------------
	//
	//		X →	Pos[0] = 1.0f
	//		Y →	Pos[1] = 4.0f
	//
	// Used to assign postion using a subscript with a float.
	//---------------------------------------

	operator float*();

	//---------------------------------------
	// POSTION		   https://bit.ly/1CcLWZV
	//---------------------------------------
	//
	//			y
	//	        |    * ← (x = 4, y = 2)
	//			|
	//	  x ----+----* ← (x = 4, y = 0)
	//		    |
	//		    |	 + ← (x = 0, y = 0)
	//			|
	//
	// Vectors postion
	//---------------------------------------

	float x;
	float y;
};

// Multiply float with Vector
Vector2 operator*(float lhs, Vector2 rhs);
