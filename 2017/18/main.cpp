#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <optional>
#include <queue>
#include <sstream>
#include <thread>
#include <vector>

constexpr int part{2};

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
	Program(int id, std::vector<std::string> instructions)
		: m_id(id),
		  m_waiting(false),
		  m_instructions(instructions),
		  m_PC(0),
		  m_lastSoundPlayed(-1),
		  m_sndCnt(0),
		  m_other(nullptr)
	{
		m_registers['p'] = m_id;
	}

	void run()
	{
		while(m_PC < m_instructions.size())
		{
			std::istringstream assembly{m_instructions[m_PC]};
			std::string instr;
			char regX;

			assembly >> instr;

			if(instr == "snd")
			{
				++m_sndCnt;
				if constexpr(part == 1)
				{
					m_lastSoundPlayed = getValue(assembly, m_registers);					
				}
				else if constexpr(part == 2)
				{
					m_other->addMessage(getValue(assembly, m_registers));
				}
			}
			else if(instr == "set")
			{
				assembly >> regX;
				m_registers[regX] = getValue(assembly, m_registers);
			}
			else if(instr == "add")
			{
				assembly >> regX;
				m_registers[regX] += getValue(assembly, m_registers);
			}
			else if(instr == "mul")
			{
				assembly >> regX;
				m_registers[regX] *= getValue(assembly, m_registers);
			}
			else if(instr == "mod")
			{
				assembly >> regX;
				m_registers[regX] %= getValue(assembly, m_registers);
			}
			else if(instr == "rcv")
			{
				if constexpr(part == 1)
				{
					if(getValue(assembly, m_registers))
					{
						std::cout << "Recovered frequency: " << m_lastSoundPlayed << std::endl;
						break;
					}				
				}
				else if constexpr(part == 2)
				{
					while(m_messages.empty())
					{
						m_waiting = true;
						if(m_other->isWaiting())
						{
							return;
						}
					}
					m_waiting = false;
					assembly >> regX;
					m_registers[regX] = getMessage().value();
				}
			}
			else if(instr == "jgz")
			{
				if(getValue(assembly, m_registers) > 0)
				{
					m_PC += getValue(assembly, m_registers);
					continue;
				}
			}
			++m_PC;
		}
		m_waiting = true;
	}

	void setOther(Program &other)
	{
		m_other = &other;
	}

	void addMessage(int message)
	{
		std::lock_guard<std::mutex> guard(m_messagesMutex);
		m_messages.push(message);
	}

	std::optional<int> getMessage()
	{
		std::lock_guard<std::mutex> guard(m_messagesMutex);
		if(!m_messages.empty())
		{
			int message{m_messages.front()};
			m_messages.pop();
			return message;
		}
		else
		{
			return {};
		}
	}

	bool isWaiting() const
	{
		return m_waiting && m_messages.empty();
	}

	size_t getSndCnt() const
	{
		return m_sndCnt;
	}

private:
	const int m_id;
	std::queue<int> m_messages;
	std::mutex m_messagesMutex;
	bool m_waiting;
	const std::vector<std::string> m_instructions;
	size_t m_PC;
	std::map<char, long int> m_registers;
	long int m_lastSoundPlayed;
	size_t m_sndCnt;
	Program *m_other;
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

	if constexpr(part == 1)
	{
		Program prog(0, instructions);
		prog.run();
	}
	else if constexpr(part == 2)
	{
		Program prog0(0, instructions);
		Program prog1(1, instructions);

		prog0.setOther(prog1);
		prog1.setOther(prog0);

		std::thread t1(&Program::run, &prog0);
		std::thread t2(&Program::run, &prog1);
		t1.join();
		t2.join();

		std::cout << "Nr of sends: " << prog1.getSndCnt() << std::endl;					 
	}
	
	return 0;
}
