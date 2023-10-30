/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
    //vector<T> data;
    n1 = 0;  
    n2 = -1;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T tempEle= data[n1++];

    if (n2-n1+1 <= n1) {
        vector<T> temp;
        for(int i=n1;i<=n2;i++)
            temp.push_back(data[i]);
        data = temp;
        n1=0;
        n2=data.size()-1;
    }

    return tempEle;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T tempEle= data[n2--];
    data.pop_back(); //This is important cause we might 
    //have operations like popR() followed by pushR(n).
    // When we do popL(), there is nothing to do with the push side(right side),
    //So we can just change the indicator n1.
    //But when we popR(), we can't just leave it there in the vctor
    // and just change the indicator n2.
    //Since the only push side is the right side.
    if (n2-n1+1 <= n1) {
        vector<T> temp;
        for(int i=n1;i<=n2;i++)
            temp.push_back(data[i]);  
        data = temp;
        n1=0;
        n2=data.size()-1;
    }

    return tempEle;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data[n1];
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data[n2];
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return n1 > n2;
}
