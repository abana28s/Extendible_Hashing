#include <bits/stdc++.h>
using namespace std;

class bucket
{
public:
    int local_depth;
    set<int> elem;
};

int main()
{
    int global_depth, bucket_capacity;
    cin >> global_depth >> bucket_capacity;
    int n = 1 << global_depth;
    vector<bucket *> dir(n);
    vector<int> buck_index;
    for (int i = 0; i < n; i++)
    {
        bucket *b = new bucket;
        b->local_depth = global_depth;
        dir[i] = b;
        buck_index.push_back(i);
    }
    int t;
    while (cin >> t)
    {
        n = 1 << global_depth;
        if (t == 2)
        {
            int x;
            cin >> x;
            int index = x % n;

            if (dir[index]->elem.find(x) != dir[index]->elem.end())
            {
                // error
                continue;
            }

            while (dir[index]->elem.size() >= bucket_capacity)
            {
                if (dir[index]->local_depth == global_depth)
                {
                    if (global_depth == 20)
                    {
                        // error
                        break;
                    }
                    for (int i = 0; i < n; i++)
                    {
                        dir.push_back(dir[i]);
                    }
                    bucket *b = new bucket;
                    int index1 = index;
                    int index2 = index + n;
                    dir[index2] = b;
                    global_depth++;
                    n = 1 << global_depth;
                    b = new bucket;
                    set<int>::iterator it;
                    b->local_depth = dir[index1]->local_depth + 1;
                    dir[index2]->local_depth = dir[index1]->local_depth + 1;
                    for (it = dir[index1]->elem.begin(); it != dir[index1]->elem.end(); it++)
                    {
                        if ((*it) % n == index1)
                        {
                            b->elem.insert(*it);
                        }
                        else
                        {
                            dir[index2]->elem.insert(*it);
                        }
                    }
                    delete dir[index1];
                    dir[index1] = b;
                    buck_index.push_back(index2);
                }
                else
                {
                    bucket *b = new bucket;

                    int a = 1 << dir[index]->local_depth;

                    int index1 = x % a;
                    int index2 = index1 + a;
                    dir[index2] = b;
                    b = new bucket;
                    set<int>::iterator it;
                    b->local_depth = dir[index1]->local_depth + 1;
                    dir[index2]->local_depth = dir[index1]->local_depth + 1;
                    a = 1 << b->local_depth;
                    for (it = dir[index1]->elem.begin(); it != dir[index1]->elem.end(); it++)
                    {
                        if ((*it) % a == index1)
                        {
                            b->elem.insert(*it);
                        }
                        else
                        {
                            dir[index2]->elem.insert(*it);
                        }
                    }
                    delete dir[index1];
                    dir[index1] = b;
                    buck_index.push_back(index2);

                    for (int i = a; index1 + i < n; i += a)
                    {
                        dir[index1 + i] = dir[index1];
                    }
                    for (int i = a; index2 + i < n; i += a)
                    {
                        dir[index2 + i] = dir[index2];
                    }
                }
                index = x % n;
            }
            index = x % n;
            dir[index]->elem.insert(x);
        }
        else if (t == 3)
        {
            int x;
            cin >> x;
            int index = x % n;
            if (dir[index]->elem.find(x) == dir[index]->elem.end())
            {
                // no
                cout << "no : " << x << endl;
            }
            else
            {
                // yes
                cout << "yes : " << x << endl;
            }
        }

        else if (t == 4)
        {
            int x;
            cin >> x;
            int index = x % n;
            if (dir[index]->elem.find(x) == dir[index]->elem.end())
            {
                // error
            }
            else
            {
                dir[index]->elem.erase(x);
            }
        }

        else if (t == 5)
        {
            cout << global_depth << endl;
            cout << buck_index.size() << endl;
            for (int i = 0; i < buck_index.size(); i++)
            {
                cout << endl;
                cout << buck_index[i] << endl;
                cout << dir[buck_index[i]]->elem.size() << " " << dir[buck_index[i]]->local_depth << endl;
                set<int>::iterator it;
                for (it = dir[buck_index[i]]->elem.begin(); it != dir[buck_index[i]]->elem.end(); it++)
                {
                    cout << *it << " ";
                }
                cout << endl;
            }
        }

        else
            return 0;
    }
    return 0;
}