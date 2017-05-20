#include "Area.h"
Area::Area() {};
Area::Area(bool locked = false) : m_locked(locked)
{	
}

Area::~Area()
{
}
void Area::AddItems(std::vector<Item> items) {
	for (auto i : items) {
		m_items.push_back(i);

	}

}
void Area::AddItem(Item item) {
	m_items.push_back(item);

}
Item Area::RemoveItem(std::string name) {
	Item item;
	for (int i = 0; i < m_items.size();++i) {
		if (m_items[i].name == name) {
			item = m_items[i];
			m_items.erase(m_items.begin() + i);
			return item;
		}
	}
	return item;
}

std::ostream & operator<<(std::ostream & stream, const Area & area)
{
	for (int i = 0; i < area.m_items.size(); ++i) {

		stream << area.m_items[i].name << (i != area.m_items.size() - 1 ? ", " : ".");
	}
	if (area.m_items.size() == 0) {
		stream << "Nothing special.";
	}
	return stream;
}
