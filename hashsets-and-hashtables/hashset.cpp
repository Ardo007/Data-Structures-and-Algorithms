#include <utility>
#include <list>
#include "hashset.hpp"


// functions to give us the begining and ending of our elements list
// so that we can iterate over the entire contents of our hash set
HashSet::Iterator HashSet::begin() {
  return elements.begin();
}

HashSet::Iterator HashSet::end() {
  return elements.end();
}

// Default constructor. initalizes my variables, as well as initalizes the 
// buckets array with each element in the bucket array to elements.end().
HashSet::HashSet() {
   maxLoadFa = 1.0;
   numOfElements = 0;
   bucket_count = sizes[0];

   buckets = new std::list<int>::iterator[bucket_count];
   for(std::size_t i = 0; i < bucket_count; i++){
    buckets[i] = elements.end();
   }
}


// Copy Constructor. First it copies all the variables from other
// then it allocated a new array of buckets which then reassigns
// iterators by first hashing to find which bucket it will go into
HashSet::HashSet(const HashSet& other) {
  maxLoadFa = other.maxLoadFa;
  numOfElements = other.numOfElements;
  bucket_count = other.bucket_count;
  elements = other.elements;

  buckets = new std::list<int>::iterator[bucket_count];

  // just like in the default constructor, initalizied all the elements
  // in buckets as elements.end()
  for(std::size_t i = 0; i < bucket_count; i++){
    buckets[i] = elements.end();
   }


   // iterating over the elements list and assigning the buckets
   for(auto it = elements.begin(); it != elements.end(); it++) {
    std::size_t idx = bucket(*it);

    if(buckets[idx] == elements.end()){
      buckets[idx] = it;
    }
   }


}

// using copy-and-swap idiom
HashSet& HashSet::operator=(HashSet other) {
  std::swap(maxLoadFa, other.maxLoadFa);
  std::swap(numOfElements, other.numOfElements);
  std::swap(bucket_count, other.bucket_count);
  std::swap(elements, other.elements);
  std::swap(buckets, other.buckets);
  return *this;
}

// freeing the dynamically allocated bucket array
HashSet::~HashSet() {
  delete[] buckets;
}


// inserting a key into our hash set
void HashSet::insert(int key) {
  if(contains(key)){  // check if the key is present, if yes do nothing
    return;
  }



  // over here we first hash the key to see which bucket it will go to
  std::size_t idx = bucket(key);

  // we get the iterator of that bucket from buckets
  auto bucket = buckets[idx];

  // we insert the element at the position (bucket) and since the element
  // gets inserted before the position we will update our buckets iterator
  auto it = elements.insert(bucket, key); // insert returns an iterator pointing to the newly inserted element

  // so we assign that new interator as our new start of the bucket in our buckets array
  buckets[idx] = it; 

  numOfElements++; // we then increase the number of elements


  // calculate the load factor after insertion to see if we need rehashing
  if(loadFactor() > maxLoadFa) {
    std::size_t newBucketCount;
    for(std::size_t size : sizes) {
      if(size > bucket_count) {
        newBucketCount = size;
        break;
      }
    }

    rehash(newBucketCount);
  }

}

// checking if an element is present or no in the hash set
// returns true if present, false if not
bool HashSet::contains(int key) const {
  std::size_t index = bucket(key); // we hash the key to see which bucket it would be in

  auto bucketIt = buckets[index]; // get the iterator of that bucket

  // then we iterate through our elements list while making sure 
  // we do not go into a different bucket using the "bucket(*bucketIt) == index" line
  while(bucketIt != elements.end() && bucket(*bucketIt) == index){
    if(*bucketIt == key) { // dereference the element at that position to check if it matches our key
      return true;
    }
    bucketIt++;
  }
  return false; // the key was not in our hash set so return false

}

// same logic as our contains function but instead we return the iterator of that element which we found
// otherwise return elements.end() if not present
HashSet::Iterator HashSet::find(int key) {
  std::size_t index = bucket(key);

  auto bucketIt = buckets[index];

  while(bucketIt != elements.end() && bucket(*bucketIt) == index){

    if(*bucketIt == key) {
      return bucketIt;
    }
    bucketIt++;

  }

  return elements.end();
}


void HashSet::erase(int key) {
  erase(find(key));
}

// erasing an elements from our elements list at the given iterator and then
// returning the iterator of the element following it
HashSet::Iterator HashSet::erase(HashSet::Iterator it) {
  if(it == elements.end()){ // nothing to erase in this case since there is no element there
    return it;
  }

  std::size_t idx = bucket(*it); // we dereference the iterator and hash it to see which bucket it will be in

  auto next = std::next(it);  // we get the iterator of the element after the iterator before any erasing


  // over here we check if the element to be erased in the first element in the bucket, aka the head, if it is
  // we then check if the next element we have belongs to the same bucket, if it does we update our head with the 
  // next element otherwise we set the head as end
  if(buckets[idx] == it) {
    if(next != elements.end() && bucket(*next) == idx){
      buckets[idx] = next;
    }
    else {
      buckets[idx] = elements.end();
    }
  }

  // we erase the element and decrease the number of elements
  elements.erase(it);
  numOfElements--;

  return next; // return the element after the erased element
}


// rehash our elements into a new bucket size
void HashSet::rehash(std::size_t newSize) {
  std::list<int>::iterator* newBuckets;
  bucket_count = newSize; // we first make sure our bucket count aka our size is updated as we are using it in our hash function

  // allocate a new array of iterators with our new size and each element pointing to elements.end()
  newBuckets = new std::list<int>::iterator[newSize];
  for(std::size_t i = 0; i < newSize; i++){
      newBuckets[i] = elements.end();
   }


  // we will then iterate through our list and moving them accordingly
   auto elemIt = elements.begin();

   while(elemIt != elements.end()){
    auto next = std::next(elemIt); // to move on to the next element

    std::size_t idx = bucket(*elemIt); // hash the element to see which new bucket it will go in

    if(newBuckets[idx] == elements.end()){ 
      // if there is no iterator at that index in our new buckets then we assign it as the head of the new bucket
      newBuckets[idx] = elemIt;
    }
    else { 
      // however if there is an element already present, we will splice the current element
      // directly at the position pointed to by newBuckets[idx] then we will move the iterator back by one
      // this esentially make the element the new head of the bucket
      elements.splice(newBuckets[idx], elements, elemIt);
      newBuckets[idx]--;
    }

    elemIt = next; // we then go to the next element
   }

   
   // delete our old buckets and replace it
   delete[] buckets;
   buckets = newBuckets;
}

// return the number of elements 
std::size_t HashSet::size() const {
  return numOfElements;
}

// return if our hash set if empty by seeing if we have 0 elements in it
bool HashSet::empty() const {
  return numOfElements == 0;
}

// return the bucket count
std::size_t HashSet::bucketCount() const {
  return bucket_count;
}

// returning the size of each bucket by counting how many elements are in that bucket
std::size_t HashSet::bucketSize(std::size_t b) const {

  std::size_t count = 0;

  auto bucketIt = buckets[b];

  // to make sure we are counting the elements in the same bucket and not in other buckets
  while(bucketIt != elements.end() && b == bucket(*bucketIt)){

    count++;
    bucketIt++;

  }
  return count;
  
}


// The Hash Function. it modulus's the key with the bucket count
// to get the remainder which is going to be the bucket that the 
// key is going to go into
std::size_t HashSet::bucket(int key) const {
    return static_cast<std::size_t>(key) % bucket_count;
}


// calculating the load factor by dividing the number of elements with the bucket count
float HashSet::loadFactor() const {
  return static_cast<float>(numOfElements)/bucket_count;
}

// returning what the max load factor is set as 
float HashSet::maxLoadFactor() const {
  return maxLoadFa;
}

// setting what hte max load factor is 
// while at the same time calculating the load factor and checking 
// if a rehash is needed with the newly set max load factor
void HashSet::maxLoadFactor(float maxLoad) {
  maxLoadFa = maxLoad;

    if(loadFactor() > maxLoadFa) {
    std::size_t newBucketCount;
    for(std::size_t size : sizes) {
      while(size > bucket_count) {
        newBucketCount = size;
        break;
      }
    }

    rehash(newBucketCount);
  }
  
}