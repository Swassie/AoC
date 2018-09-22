#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

constexpr int part{2};

long int optimized(long int input)
{
	long int a{1}, b{0}, c{0}, d{0}, e{0}, f{0}, g{0}, h{0};

	b = input;
	c = b;

	if(a != 0)
	{
		b *= 100;
		b -= -100000;
		c = b;
		c -= -17000;
	}

	while(1){
		f = 1;
		d = 2;
		do
		{
			e = 2;
			if(e <= b / d && b > b / d && b % d == 0)
			{
				f = 0;
			}
			e = b;
			++d;
			g = d - b;
		}while(g != 0);

		if(f == 0)
		{
			++h;
		}
		g = b - c;
		
		if(g == 0)
		{
			break;
		}
		b += 17;
	}
	
	return h;
}

long int getValue(std::istringstream &stream, std::map<char, long int> &registers)
{
	long int nr;
	char reg;
	
	stream >> nr;
	if(!stream.fail())
	{
		return nr;
	}
	else
	{
		stream.clear();
		stream >> reg;
		return registers[reg];
	}
}

class Program
{
public:
	Program(std::vector<std::string> instructions)
		: m_instructions(instructions),
		  m_PC(0),
		  m_mulCnt(0) {}

	void run()
	{
		while(m_PC < m_instructions.size())
		{
			std::istringstream assembly{m_instructions[m_PC]};
			std::string instr;
			char regX;

			assembly >> instr;

			if(instr == "set")
			{
				assembly >> regX;
				m_registers[regX] = getValue(assembly, m_registers);
			}
			else if(instr == "sub")
			{
				assembly >> regX;
				m_registers[regX] -= getValue(assembly, m_registers);
			}
			else if(instr == "mul")
			{
				assembly >> regX;
				m_registers[regX] *= getValue(assembly, m_registers);
				++m_mulCnt;
			}
			else if(instr == "jnz")
			{
				if(getValue(assembly, m_registers) != 0)
				{
					m_PC += getValue(assembly, m_registers);
					continue;
				}
			}
			++m_PC;
		}
	}

	size_t getMulCnt() const
	{
		return m_mulCnt;
	}

private:
	const std::vector<std::string> m_instructions;
	size_t m_PC;
	std::map<char, long int> m_registers;
	size_t m_mulCnt;
};

int main()
{
	std::ifstream file{"../input.txt"};
	std::string tempString;
	std::vector<std::string> instructions;
	
	while(std::getline(file, tempString))
	{
		instructions.push_back(tempString);
	}

	Program prog(instructions);
	
	if constexpr(part == 1)
	{
		prog.run();
		std::cout << "Nr of muls: " << prog.getMulCnt() << std::endl;
	}
	else if constexpr(part == 2)
	{
		std::istringstream stream{instructions[0]};
		stream.ignore(6);
		long int b, h;
		stream >> b;
		h = optimized(b);
		std::cout << "h = " << h << std::endl;
	}
	
	return 0;
}
