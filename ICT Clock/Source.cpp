#include<windows.h>
#include<time.h>
#include<math.h>
#define screen_x 32
#define screen_y 8
#define scount 80
#define menuSize 5
#define TextSpeed 100
#define MenuDelay 100
struct  Time
{
	void reset() { hour = 0, minuite = 0, second = 0; }
	int hour = 0, minuite = 0, second = 0;
	virtual void Plus(int hour, int minuite, int second) {
		this->hour += hour;
		this->minuite += minuite;
		this->second += second;
		if (this->second >= 0) {
			this->minuite += this->second / 60;
			this->second %= 60;
		}
		else {
			while (this->second < 0) {
				this->second += 60;
				this->minuite--;
			}
		}
		if (this->minuite >= 0) {
			this->hour += this->minuite / 60;
			this->minuite %= 60;
		}
		else {
			while (this->minuite < 0) {
				this->minuite += 60;
				this->hour--;
			}
		}
		if (this->hour < 0) {
			reset();
		}

	}
	bool isZero() {
		return !(hour != 0 || minuite != 0 || second != 0);
	}
};
struct  ClockTime :public Time {
	void Plus(int hour, int minuite, int second) {
		this->hour += hour;
		this->minuite += minuite;
		this->second += second;
		if (this->second >= 0) {
			this->minuite += this->second / 60;
			this->second %= 60;
		}
		else {
			while (this->second < 0) {
				this->second += 60;
				this->minuite--;
			}
		}
		if (this->minuite >= 0) {
			this->hour += this->minuite / 60;
			this->minuite %= 60;
		}
		else {
			while (this->minuite < 0) {
				this->minuite += 60;
				this->hour--;
			}
		}
		if (this->hour < 0) {
			while (this->hour < 0) {
				this->hour += 24;
			}
		}
		this->hour %= 24;
	}
	void PlusHourDigit(const int& number, int digit) {
		if (digit == 0) {
		int a = this->hour / 10+number;
		for (; a < 0; a += 3);
		a %= 3;
		if (a == 2 && this->hour % 10 >= 4) {
			this->hour = 20;
		}
		else {
			this->hour = a * 10 + this->hour % 10;
		}
		}
		else if (digit == 1) {
			int a = this->hour % 10 + number;
			if (this->hour / 10 == 2) 
				for (; a < 0; a += 4);
			else
				for (; a < 0; a += 10);
			a %= 10;
			if (this->hour / 10 == 2 && a >= 4) {
				this->hour = 20;
			}
			else {
				this->hour = a + (this->hour / 10) * 10;
			}
		}
		else if (digit == 2) {
			int a = this->minuite / 10 +number;
			for (; a < 0; a += 6);
			a %= 6;
			this->minuite = a * 10 + this->minuite % 10;
		}
		else if (digit == 3) {
			int a = this->minuite % 10 + number;
			for (; a < 0; a += 10);
			a %= 10;
			this->minuite = a  + (this->minuite/10) *10;
		}
	}
};
struct Vector2 {
	int X = 0, Y = 0;
	Vector2() {}
	Vector2(const int& x, const int& y) :X(x), Y(y) {}
	Vector2 operator+(const Vector2& vecPlus) {
		X += vecPlus.X;
		Y += vecPlus.Y;
	}
};

int alphabets[26][7] = {
{0x0e,0x11,0x11,0x1f,0x11,0x11,0x11},
{0x1e,0x11,0x11,0x1e,0x11,0x11,0x1e},
{0x0f,0x10,0x10,0x10,0x10,0x10,0x0f},
{0x1e,0x11,0x11,0x11,0x11,0x11,0x1e},
{0x1f,0x10,0x10,0x1f,0x10,0x10,0x1f},
{0x1f,0x10,0x10,0x1f,0x10,0x10,0x10},
{0x0e,0x10,0x10,0x13,0x11,0x11,0x0e},
{0x11,0x11,0x11,0x1f,0x11,0x11,0x11},
{0x1f,0x04,0x04,0x04,0x04,0x04,0x1f},
{0x07,0x01,0x01,0x01,0x01,0x11,0x0e},
{0x11,0x12,0x14,0x18,0x14,0x12,0x11},
{0x10,0x10,0x10,0x10,0x10,0x10,0x1f},
{0x11,0x11,0x1b,0x15,0x11,0x11,0x11},
{0x11,0x11,0x19,0x15,0x13,0x11,0x11},
{0x1f,0x11,0x11,0x11,0x11,0x11,0x1f},
{0x1e,0x11,0x11,0x1e,0x10,0x10,0x10},
{0x0e,0x11,0x11,0x11,0x11,0x12,0x0d},
{0x1e,0x11,0x11,0x1e,0x11,0x11,0x11},
{0x0f,0x10,0x10,0x0e,0x01,0x01,0x1e},
{0x1f,0x04,0x04,0x04,0x04,0x04,0x04},
{0x11,0x11,0x11,0x11,0x11,0x11,0x0e},
{0x11,0x11,0x11,0x0a,0x0a,0x04,0x04},
{0x11,0x11,0x15,0x15,0x15,0x1b,0x11},
{0x11,0x11,0x0a,0x04,0x0a,0x11,0x11},
{0x11,0x11,0x0a,0x04,0x04,0x04,0x04},
{0x1f,0x01,0x02,0x04,0x08,0x10,0x1f}
},
numbers[10][7] = {
{0x0e,0x11,0x13,0x15,0x19,0x11,0x0e},
{0x04,0x0c,0x04,0x04,0x04,0x04,0x04},
{0x1e,0x01,0x01,0x02,0x04,0x08,0x1f},
{0x1e,0x01,0x01,0x1e,0x01,0x01,0x1e},
{0x11,0x11,0x11,0x1f,0x01,0x01,0x01},
{0x1f,0x10,0x10,0x1e,0x01,0x01,0x1e},
{0x0e,0x10,0x10,0x1e,0x11,0x11,0x0e},
{0x1f,0x01,0x01,0x02,0x02,0x04,0x04},
{0x0f,0x11,0x11,0x0e,0x11,0x11,0x0e},
{0x0f,0x11,0x11,0x0f,0x01,0x01,0x0e}
};

int getStringSize(const char* string) { int i = 0; for (; string[i] != '\0'; i++); return i; }
bool isPressS, isPressD, isPressE, isPressA;

//
HANDLE wHnd, rHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
Vector2 bufferSize = { screen_x,screen_y }, characterPos = { 0,0 }, star[scount], ShipPos;
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
DWORD fdwMode, numEvents = 0, numEventsRead = 0;

//OutSource
void CheckKeyPress() {
	static time_t lastframe;
	isPressS = false, isPressD = false, isPressE = false, isPressA = false;
	if (clock() > lastframe + 100) {
		lastframe = clock();
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT) {
					if (eventBuffer[i].Event.KeyEvent.bKeyDown) {
						if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 's') {
							isPressS = true;
						}
						if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'd') {
							isPressD = true;
						}
						if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'e') {
							isPressE = true;
						}
						if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'a') {
							isPressA = true;
						}
					}
				}
			}
			delete[] eventBuffer;
		}
	}
}
COORD GetCOORD(const Vector2& vec) {
	COORD a;
	a.X = vec.X;
	a.Y = vec.Y;
	return a;
}
int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}
int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, GetCOORD(bufferSize));
	return 0;
}
void clear_buffer()
{
	for (int x = 0; x < screen_x; ++x) {
		for (int y = 0; y < screen_y; ++y) {
			consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
			consoleBuffer[x + screen_x * y].Attributes = 7;
		}
	}
}
void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, GetCOORD(bufferSize), GetCOORD(characterPos),
		&windowSize);
}
//Extension

void Draw(int x, int y, bool b) {
	consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
	if (b)
		consoleBuffer[x + screen_x * y].Attributes = 120;
	else
		consoleBuffer[x + screen_x * y].Attributes = 20;
}
bool GetBufferAt(const int& x, const int& y) {
	if (consoleBuffer[x + screen_x * y].Attributes == 120)
		return true;
	else
		return false;
}
void DrawFullRect(Vector2 startPos, Vector2 size, bool b) {
	for (size_t i = 0; i < size.Y; i++) {
		if (startPos.Y + i < screen_y) {
			for (size_t j = 0; j < size.X; j++)
			{
				if (startPos.X + i < screen_x) {
					Draw(startPos.X + j, startPos.Y + i, b);
				}
			}
		}
	}

}
void DrawCharanctor(const char& c, const Vector2& startPos, bool b) {
	if (c <= '9' && c >= '0') {
		for (int i = 0; i < 7; i++) {
			if (startPos.Y + i > screen_y)
				break;
			int p = (int)pow(2, 4);
			for (int j = 0; j < 5; j++, p /= 2) {
				if (startPos.X + j > screen_x)
					break;
				if (startPos.X + j >= 0 && startPos.Y + i >= 0) {
					if (b)
						Draw(startPos.X + j, startPos.Y + i, (numbers[c - '0'][i] & p));
					else
						Draw(startPos.X + j, startPos.Y + i, !(numbers[c - '0'][i] & p));
				}

			}
		}
	}
	else if (c <= 'z' && c >= 'a') {
		for (int i = 0; i < 7; i++) {
			if (startPos.Y + i > screen_y)
				break;
			int p = (int)pow(2, 4);
			for (int j = 0; j < 5; j++, p /= 2) {
				if (startPos.X + j > screen_x)
					break;
				if (startPos.X + j >= 0 && startPos.Y + i >= 0) {
					if (b)
						Draw(startPos.X + j, startPos.Y + i, (alphabets[c - 'a'][i] & p));
					else
						Draw(startPos.X + j, startPos.Y + i, !(alphabets[c - 'a'][i] & p));
				}
			}
		}
	}
	else if (c <= 'Z' && c >= 'A') {
		for (int i = 0; i < 7; i++) {
			if (startPos.Y + i > screen_y)
				break;
			int p = (int)pow(2, 4);
			for (int j = 0; j < 5; j++, p /= 2) {
				if (startPos.X + j > screen_x)
					break;
				if (startPos.X + j >= 0 && startPos.Y + i >= 0)
					if (b)
						Draw(startPos.X + j, startPos.Y + i, (alphabets[c - 'A'][i] & p));
					else
						Draw(startPos.X + j, startPos.Y + i, !(alphabets[c - 'A'][i] & p));
			}
		}
	}
}
void DrawString(char* st, const Vector2& startPos) {
	for (int i = 0; *st != '\0'; i++, st++) {
		DrawCharanctor(*st, Vector2(i * 6 + startPos.X, startPos.Y), true);
	}
}
void DrawTime(const int& first, const int& second) {
	DrawCharanctor('0' + first / 10, Vector2(1, 1), true);
	DrawCharanctor('0' + first % 10, Vector2(7, 1), true);
	Draw(13, 5, true);
	Draw(13, 3, true);
	DrawCharanctor('0' + second / 10, Vector2(16, 1), true);
	DrawCharanctor('0' + second % 10, Vector2(22, 1), true);
}

class State {
public:
	virtual void CheckKeyPress() {}
	virtual void DrawBuffer() {}
	virtual void SetUp() {}
	virtual void Update() {}
};
State* state;
State* d_menuState();
void ChangeState(State*& state, State* changestate) {
	state = changestate;
	state->SetUp();
}
class NormalState :public State {
public:
	void SetUp() override
	{
	}
	void CheckKeyPress()override
	{
		if (isPressA || isPressD || isPressE || isPressS) {
			ChangeState(state, d_menuState());
		}
	}
	void DrawBuffer()override
	{
		DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), false);
		DrawTime(12, 25);
	}
	void Update() override
	{
	}
}normalState;
class TimerState :public State {
	Time thisTime;
	bool isEditTime;
	bool isEditNumber;
	bool isEnd;
	int choosedigit;
public:
	void SetUp() override
	{
		thisTime.reset();
		isEditTime = true;
		choosedigit = 0;
	}
	void CheckKeyPress()override
	{
		if (isEditNumber) {
			if (isPressS) {
				switch (choosedigit) {
				case 0:thisTime.minuite = thisTime.minuite % 10 + (((thisTime.minuite / 10) + 5) % 6) * 10; break;
				case 1:thisTime.minuite = (thisTime.minuite / 10) * 10 + (((thisTime.minuite % 10) + 5) % 6); break;
				case 2:thisTime.second = thisTime.second % 10 + (((thisTime.second / 10) + 5) % 6) * 10; break;
				case 3:thisTime.second = (thisTime.second / 10) * 10 + (((thisTime.second % 10) + 9) % 10); break;
				}
			}
			if (isPressD) {
				switch (choosedigit) {
				case 0:thisTime.minuite = thisTime.minuite % 10 + (((thisTime.minuite / 10) + 1) % 10) * 10; break;
				case 1:thisTime.minuite = (thisTime.minuite / 10) * 10 + (((thisTime.minuite % 10) + 1) % 10); break;
				case 2:thisTime.second = thisTime.second % 10 + (((thisTime.second / 10) + 1) % 6) * 10; break;
				case 3:thisTime.second = (thisTime.second / 10) * 10 + (((thisTime.second % 10) + 1) % 10); break;
				}
			}
			if (isPressE) {
				isEditNumber = false;
				isEditTime = false;
				isEnd = false;
			}
			if (isPressA) {
				isEditNumber = false;
			}
		}
		else if (isEditTime) {
			if (isPressS) {
				choosedigit = (choosedigit + 3) % 4;
			}
			if (isPressD) {
				choosedigit = (choosedigit + 1) % 4;
			}
			if (isPressE) {
				isEditNumber = true;
			}
			if (isPressA) {
				ChangeState(state, d_menuState());
			}
		}
		else {
			if (isPressA) {
				isEditTime = true;
			}
		}
	}
	void DrawBuffer()override
	{
		if (isEnd) {
			static time_t t;
			static bool b;
			if (clock() > t + 100) {
				t = clock();
				b = !b;
			}
			DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), b);
		}
		else {
			DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), false);
			DrawTime(thisTime.hour * 60 + thisTime.minuite, thisTime.second);
		}
		if (isEditTime) {
			Vector2 offset;
			switch (choosedigit)
			{
			case 0: offset = Vector2(0, 0); break;
			case 1: offset = Vector2(6, 0); break;
			case 2: offset = Vector2(15, 0); break;
			case 3: offset = Vector2(21, 0); break;
			}
			for (int i = 0; i < 8; i++) {
				if (offset.Y + i < 0)
					continue;
				if (offset.Y + i < screen_y) {
					for (int j = 0; j < 6; j++) {
						if (offset.X + j < 0)
							continue;
						if (offset.X + j < screen_x)
							Draw(offset.X + j, offset.Y + i, !GetBufferAt(offset.X + j, offset.Y + i));
					}
				}
			}
		}
	}
	void Update() override
	{
		if (!isEditTime) {
			static time_t lastframe;
			if (clock() > lastframe + 1000) {
				lastframe = clock();
				static int count;
				if (!isEnd) {
					thisTime.Plus(0, 0, -1);
					if (thisTime.isZero()) {
						isEnd = true;
					}
				}
				else if (++count > 3) {
					isEnd = false;
					thisTime.reset();
					isEditTime = true;
				}
			}
		}
	}
}timerState;
class StopWatchState :public State {
public:
	Time thisTime;
	bool isStart;
	void SetUp() override
	{
		thisTime.reset();
		isStart = false;
	}
	void CheckKeyPress()override
	{
		if (isPressE) {
			isStart = !isStart;
		}
		if (isPressA) {
			if (!isStart) {
				if (thisTime.isZero()) {
					ChangeState(state, d_menuState());
				}
				else {
					thisTime.reset();
				}
			}
		}
	}
	void DrawBuffer()override
	{
		DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), false);
		DrawTime(thisTime.hour * 60 + thisTime.minuite, thisTime.second);
	}
	void Update() override
	{
		if (isStart) {
			static time_t t = clock();
			if (clock() > t + 1000) {
				t = clock();
				thisTime.Plus(0, 0, 1);
			}
		}
	}
}stopWatchState;
class AlarmState :public State {
	enum Mode {
		Choose,
		Delete,
		Create
	}mode;
	enum SubMode {
		EditDigit,
		EditNumber
	}subMode;
	char listName[2][20] = { "New Alarm","Delete Alarm" };
	int textOffset;
	int currentChoosing = 0;
	ClockTime newTime;
	int choosedigit;
	int currentAlarmTimeIndex;
	ClockTime alarmTimes[10];
	int alarmTimeSize = 0;
public:
	void moveText() {
		if (-textOffset < (getStringSize(listName[currentChoosing]) - 3) * 6)
			textOffset--;
		else
			textOffset = 5;
	}
	void MoveUp() {
		static time_t t;
		if (clock() > t + MenuDelay) {
			t = clock();
			textOffset = 5;
			currentChoosing = !currentChoosing;
		}
	}
	void MoveDown() {
		static time_t t;
		if (clock() > t + MenuDelay) {
			t = clock();
			textOffset = 5;
			currentChoosing = !currentChoosing;
		}
	}
	void SetUp() override
	{
		textOffset = 5;
		currentChoosing = 0;
		mode = Choose;
	}
	void CheckKeyPress()override
	{
		if (mode == Choose) {
			if (isPressA) {
				ChangeState(state, &normalState);
			}
			if (isPressS) {
				MoveUp();
			}
			if (isPressD) {
				MoveDown();
			}
			if (isPressE) {
				switch (currentChoosing)
				{
				case 0:mode = Create; subMode = EditDigit; newTime.reset(); break;
				case 1:if (alarmTimeSize)mode = Delete; currentAlarmTimeIndex = 0; break;
				}
			}
		}
		else if (mode == Create) {
			if (subMode == EditNumber) {
				if (isPressS) {
					switch (choosedigit) {
					case 0:newTime.PlusHourDigit(-1, 0); break;
					case 1:newTime.PlusHourDigit(-1, 1); break;
					case 2:newTime.PlusHourDigit(-1, 2); break;
					case 3:newTime.PlusHourDigit(-1, 3); break;
					}
				}
				if (isPressD) {
					switch (choosedigit) {
					case 0:newTime.PlusHourDigit(1, 0); break;
					case 1:newTime.PlusHourDigit(1, 1); break;
					case 2:newTime.PlusHourDigit(1, 2); break;
					case 3:newTime.PlusHourDigit(1, 3); break;
					}
				}
				if (isPressE) {
					alarmTimes[alarmTimeSize++] = newTime;
					mode = Choose;
				}
				if (isPressA) {
					subMode = EditDigit;
				}
			}
			else if (subMode == EditDigit) {
				if (isPressS) {
					choosedigit = (choosedigit + 3) % 4;
				}
				if (isPressD) {
					choosedigit = (choosedigit + 1) % 4;
				}
				if (isPressE) {
					subMode = EditNumber;
				}
				if (isPressA) {
					mode = Choose;
				}
			}
		}
		else if (mode == Delete) {
			if (isPressS) {
				currentAlarmTimeIndex = (currentAlarmTimeIndex + alarmTimeSize - 1) % alarmTimeSize;
			}
			if (isPressD) {
				currentAlarmTimeIndex = (currentAlarmTimeIndex + 1) % alarmTimeSize;
			}
			if (isPressE) {
				for (int i = currentAlarmTimeIndex; i + 1 < alarmTimeSize; i++) {
					alarmTimes[i] = alarmTimes[i + 1];
				}
				alarmTimeSize--;
			}
			if (isPressA) {
				mode = Choose;
			}
		}
	}
	void DrawBuffer()override
	{
		if (mode == Choose) {
			DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), false);
			DrawString(listName[currentChoosing], Vector2(8 + textOffset, 1));
			DrawFullRect(Vector2(0, 0), Vector2(7, screen_y), true);
			DrawCharanctor(currentChoosing + '1', Vector2(1, 1), false);
		}
		else if (mode == Create) {
			DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), false);
			DrawTime(newTime.hour, newTime.minuite);
			Vector2 offset;
			switch (choosedigit)
			{
			case 0: offset = Vector2(0, 0); break;
			case 1: offset = Vector2(6, 0); break;
			case 2: offset = Vector2(15, 0); break;
			case 3: offset = Vector2(21, 0); break;
			}
			for (int i = 0; i < 8; i++) {
				if (offset.Y + i < 0)
					continue;
				if (offset.Y + i < screen_y) {
					for (int j = 0; j < 6; j++) {
						if (offset.X + j < 0)
							continue;
						if (offset.X + j < screen_x)
							Draw(offset.X + j, offset.Y + i, !GetBufferAt(offset.X + j, offset.Y + i));
					}
				}
			}
		}
		else if (mode == Delete) {
			DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), false);
			DrawTime(alarmTimes[currentAlarmTimeIndex].hour , alarmTimes[currentAlarmTimeIndex].minuite);
		}
	}
	void Update() override
	{
		if (mode == Choose) {
			static time_t t = clock();
			if (clock() > t + TextSpeed) {
				t = clock();
				moveText();
			}
		}
		else if (mode == Create) {

		}
		else if (mode == Delete) {

		}
	}
}alarmState;
class GameState :public State {
	enum Mode {
		Stop,
		Play
	};
	int boxOffset;
	int jumpOffsets[36] = {-1,-1,-2,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-2,-1,-1,0};
	int jumpOffsetSize =36;
	int currentjumpOffset;
	Mode mode = Stop;
	int walls[20];
	int wallSize=0;
	int floatWalls[20];
	int floatWallSize = 0;
	bool isJump;
	time_t moveSpeed;
public:
	void SetUp() override
	{
		mode = Stop;
		moveSpeed = 50;
	}
	void CheckKeyPress()override
	{
		if (mode == Stop) {
			if (isPressE) {
				mode = Play;
				wallSize = 0;
				floatWallSize = 0;
			}
			if (isPressA) {
				ChangeState(state, d_menuState());
			}
		}
		else if (mode == Play) {
			if (isPressE) {
				Jump();
			}
			if (isPressA) {
				ChangeState(state,d_menuState());
			}
		}
	}
	void DrawFloor() {
		DrawFullRect(Vector2(0, 7), Vector2(32, 1), true);
	}
	void DrawBox() {
		DrawFullRect(Vector2(1, 4 + boxOffset), Vector2(3,3), true);
	}
	void DrawWall() {
		for (int i = 0; i < wallSize; i++) {
			DrawFullRect(Vector2(walls[i], 5), Vector2(2, 2), true );
		}
		for (int i = 0; i < floatWallSize; i++) {
			DrawFullRect(Vector2(floatWalls[i], 1), Vector2(3, 3), true);
		}
	}
	void DrawBuffer()override
	{
		DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), false);
		DrawFloor();
		DrawBox();
		DrawWall();
	}
	void Jump(){
		isJump = true;
		currentjumpOffset = 0;
	}
	void Update() override
	{
		if (mode == Play) {
			static time_t t,t1,t2;
			static int count = 0;
			if (clock() > t + moveSpeed) {
				t = clock();
				for (int i = 0; i < wallSize; i++) {
					walls[i]--;
					if (walls[i]<-1) {
						for (int j = 1; j < wallSize; j++) {
							walls[j - 1] = walls[j];
						}
						wallSize--;
					}
				}
				for (int i = 0; i < floatWallSize; i++) {
					floatWalls[i]--;
					if (floatWalls[i] < -1) {
						for (int j = 1; j < floatWallSize; j++) {
							floatWalls[j - 1] = floatWalls[j];
						}
						floatWallSize--;
					}
				}
				if (++count > 100) {
					count = 0;
					moveSpeed *= 0.98;
				}
			}
			time_t jumptime = (time_t)(moveSpeed * 0.4);
			if (clock() > t1 + jumptime) {
				t1 = clock();
				if (isJump) {
					boxOffset = jumpOffsets[++currentjumpOffset];
					if (currentjumpOffset + 1 == jumpOffsetSize) {
						isJump = false;
					}
				}
			}
			time_t instantTime= 30*moveSpeed;
			if (clock() > t2 + instantTime) {
				t2 = clock();
				if(rand()%3>0)
					walls[wallSize++]=32;
				else
					floatWalls[floatWallSize++] = 32;
			}
		}
	}
}gameState;
class MenuState :public State {
	char listName[menuSize][20] = { "Set Time","Timer","Stop Watch","Alarm","Game" };
	int currentChoosing = 0;
	time_t currentTime;
	time_t lastframe;
	int textOffset;
public:
	void moveText() {
		if (-textOffset < (getStringSize(listName[currentChoosing]) - 3) * 6)
			textOffset--;
		else
			textOffset = 5;
	}
	void MoveUp() {
		lastframe = clock();
		textOffset = 5;
		currentChoosing = (currentChoosing + menuSize - 1) % menuSize;
	}
	void MoveDown() {
		lastframe = clock();
		textOffset = 5;
		currentChoosing = (currentChoosing + 1) % menuSize;
	}
	void SetUp() override
	{
		lastframe = clock();
		textOffset = 5;
		currentChoosing = 0;
	}
	void CheckKeyPress()override
	{
		if (isPressA) {
			ChangeState(state, &normalState);
		}
		if (isPressS) {
			MoveUp();
		}
		if (isPressD) {
			MoveDown();
		}
		if (isPressE) {
			switch (currentChoosing)
			{
			case 0:ChangeState(state, &normalState); break;
			case 1:ChangeState(state, &timerState); break;
			case 2:ChangeState(state, &stopWatchState); break;
			case 3:ChangeState(state, &alarmState); break;
			case 4:ChangeState(state, &gameState); break;
			}
		}

	}
	void DrawBuffer()override
	{
		DrawFullRect(Vector2(0, 0), Vector2(screen_x, screen_y), false);
		DrawString(listName[currentChoosing], Vector2(8 + textOffset, 1));
		DrawFullRect(Vector2(0, 0), Vector2(7, screen_y), true);
		DrawCharanctor(currentChoosing + '1', Vector2(1, 1), false);
	}
	void Update() override
	{
		currentTime = clock();
		if (currentTime > lastframe + TextSpeed) {
			lastframe = currentTime;
			moveText();
		}
	}

}menuState;
State* d_menuState() { return &menuState; }

int main()
{
	srand(time(NULL));
	ChangeState(state, &normalState);
	setMode();
	setConsole(screen_x, screen_y);
	while (1) {
		CheckKeyPress();
		state->CheckKeyPress();
		state->Update();
		state->DrawBuffer();
		fill_buffer_to_console();
		clear_buffer();
	}
	return 0;
}
