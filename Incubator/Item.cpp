#include "Item.h"

int Item::itemCounter = 0;

Item::Item(Item* prev)
{
  id = itemCounter;
  setName("");
  previousItem = prev;
  nextItem = NULL;
}

void Item::setName(String n)
{
  itemName = n;
}
void Item::setHandler(Handlers::handler h)
{
  itemHandler = h;
}

int Item::getID()
{
  return id;
}
String Item::getName()
{
  return itemName;
}
Handlers::handler Item::getHandler()
{
  return itemHandler;
}

void Item::createNextItem()
{
  itemCounter++;
  nextItem = new Item(this);
}
void Item::setNextItem(Item* i)
{
  nextItem = i;
}
Item* Item::getNextItem()
{
  return nextItem;
}
Item* Item::getPreviousItem()
{
  return previousItem;
}
