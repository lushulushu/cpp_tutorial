#include <string>
#include <vector>
#include <cassert>

using std::vector;
using std::string;
int main() {
  // a vector instance
  vector<string> v1 = { "a", "ab", "abc" };

  // an array of vector instances
  vector<string> v2[2] = {
          { "a", "ab", "abc" },
          { "1", "12", "123" }
  };

  // a pointer to a vector
  vector<string>* vp;

  // vp point to v1
  vp = &v1;

  assert(*vp == v1);
  assert(vp[0] == v1);
  // access first element
  assert(vp[0][0] == "a");
  // using arrow
  assert(vp->at(2) == "abc");
  // this is also legal
  assert((*vp)[1] == "ab");

  // this will crash because there is only 1 instance
  // vp[1][0] = "a";

  // vp now point to the first instance of v2 array
  vp = v2;

  assert(vp[0][0] == "a");
  // vp[1] represent the second instance
  assert(vp[1][0] == "1");
  assert((*vp)[1] == "ab");

  // vp now point to the second instance
  vp++;

  assert(vp[0][0] == "1");
  assert((*vp)[1] == "12");

  // this will crash because there is only 1 instance after vp
  //  vp[1][0] = "1";

  return 0;
}
