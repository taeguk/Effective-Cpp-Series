class Base
{
	virtual void normal_function() final {};
	virtual void virtual_function() {};
};

class Derived : public Base
{
	// void normal_function() {};  // COMPILE ERROR
	virtual void virtual_function() override {};
};