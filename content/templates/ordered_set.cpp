#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main() {
    ordered_set s;
    s.insert(5);
    s.insert(3);
    cout << (*s.find_by_order(0)) << "\n"; // -> 3
    cout << s.order_of_key(4);
	return 0;
}
