#include <iostream>

using namespace std;


template<class tpltype> class stack
{
public:
  stack(unsigned long size);
  int push(tpltype newitem);
  tpltype pop(void);
  unsigned long count();
private:
  tpltype* data;
  unsigned long stacksize;
  unsigned long top;
};



template<class tpltype> stack<tpltype>::stack(unsigned long size)
{
  data=new tpltype[size];
  stacksize=size;
  top=0;
} // stack()

template<class tpltype> int stack<tpltype>::push(tpltype newitem)
{
  if(top >= stacksize) return -1;
  data[top]=newitem;
  top ++;
  return 0;
} // push()

template<class tpltype> tpltype stack<tpltype>::pop(void)
{
  if(top > 0) top--;
  return data[top];
} // pop()

template<class tpltype> unsigned long stack<tpltype>::count(void)
{
  return top;
} // count()


int main()
{
  stack<int> intstack(5);
  stack<double> doublestack(7);
  stack<string> stringstack(3);

  cout << "intstack bevat " << intstack.count() << " elementen:\n";
  while(intstack.count()) cout << intstack.pop() << endl;
  cout << intstack.push(3) << endl;
  cout << intstack.push(8) << endl;
  cout << intstack.push(2) << endl;
  cout << intstack.push(3) << endl;
  cout << intstack.push(125) << endl;
  cout << intstack.push(125) << endl;
  cout << intstack.push(125) << endl;
  cout << "intstack bevat " << intstack.count() << " elementen:\n";
  while(intstack.count()) cout << intstack.pop() << endl;

  doublestack.push(3.5);
  cout << "doublestack bevat " << doublestack.count() << " elementen:\n";
  while(doublestack.count()) cout << doublestack.pop() << endl;
  cout << endl;

  stringstack.push("Vuurwerk, wat een lol");
  stringstack.push("We genieten ervan hoor");
  cout << "stringstack bevat " << stringstack.count() << " elementen:\n";
  while(stringstack.count()) cout << stringstack.pop() << endl;
  cout << endl;

  return 0;
}

