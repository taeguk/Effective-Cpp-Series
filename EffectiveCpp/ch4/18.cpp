
class BadDate {
public:
	BadDate(int month, int day, int year);
};

class Month {
public:
	static Month Jan;    // Incorrect!
	static const Month& Feb() {    // Bad!
		static Month m(2);
		return m;
	}
	static Month Mar() { return Month(3); }    // Good!

private:
	explicit Month(int m)
		: month(m) {}
	int month;
};
Month Month::Jan(1);

struct Day {
	explicit Day(int d)
		: day(d) {}
	int day;
};

struct Year {
	explicit Year(int y)
		: year(y) {}
	int year;
};

class Date {
public:
	Date(Month month, Day day, Year year);
};

int main() {
	//BadDate badDate(1996, 2, 2);	// mistake of user!
	//Date date(Month::Feb(), Day(2), Year(1996));

	Year *pYear = new Year(1);
}