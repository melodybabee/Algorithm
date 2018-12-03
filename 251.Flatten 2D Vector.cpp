题意：
设计一个程序把一个二维数组压平成一位数组。
思路：
1.因为二维数组是排好序的，因此只要在一位数组中一个一个从尾部插入二维数组的元素即可。
注意vector.insert()方法，第一个系数表示位置，后面两个系数表示插入数组的头部和尾部迭代器，即插入位置。
2.如果一位数组没有到尾部，那么返回ture;
3.设置一个全局变量作为迭代器，依次从一位数组中输出数字即可。
class Vector2D {
private:
    vector<int>vec;
    int index = 0;
public:
    Vector2D(vector<vector<int>>& vec2d) {
        for(int i = 0; i< vec2d.size();++i)
        vec.insert(vec.end(),vec2d[i].begin(),vec2d[i].end());
    }

    int next() {
        int ret = vec[index];
        ++index;
        return ret;
    }

    bool hasNext() {
        if( index >= vec.size()) return false;
        return true;
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */
方法2：用C++ itertors来做，自定义一个迭代器。
思路：
1.自定义两个迭代器，一个指向二维数组的头部，表示行，一个指向二维数组的尾部
2.当头部迭代器不在最后一行且自定义的坐标不等于当行的最后一位时，头部迭代器跳至最后一行，列归0.返回头部迭代器是否等于尾部迭代器。
3.输出数字的时候，输出头部迭代器所在行的第y位，注意y++是先赋值再做加操作。
class Vector2D {
private:
    vector<vector<int>>::iterator begin,end;
    int y = 0;
public:
    Vector2D(vector<vector<int>>& vec2d) {
        begin = vec2d.begin();
        end = vec2d.end();
    }

    int next() {
        return (*begin)[y++];
    }

    bool hasNext() {
        while(begin != end && y == (*begin).size()){
            ++begin;
            y = 0;
        }
        return begin != end;
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */