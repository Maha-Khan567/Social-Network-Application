#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<sstream>
#include <string>
#include<stdexcept>
using namespace std;
class Page;
class Post;
class User;
// Member 1 code
class Date {
private:
	int day, month, year;
	bool isLeapYear(int y)const {
		return(y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}
	int daysInMonth(int m, int y) const {
		if (m < 1 || m > 12)
			throw invalid_argument("Invalid month!");
		if (m == 2)
			return isLeapYear(y) ? 29 : 28;
		if (m == 4 || m == 6 || m == 9 || m == 11)
			return 30;
		return 31;
	}
	void validate(int d, int m, int y) const {
		if (y < 0)
			throw invalid_argument("Year cannot be negative.");
		if (m < 1 || m > 12)
			throw invalid_argument("Month must be between 1 and 12.");
		int totalDays = daysInMonth(m, y);
		if (d < 1 || d > totalDays)
			throw invalid_argument("Invalid day for given month.");
	}
public:
    Date() {
	day = 0;
	month = 0;
	year = 0;
    }
	Date(int d, int m, int y) {
		validate(d,m,y);
		day = d;
		month = m;
		year = y;
	}
	void setDate(int d, int m, int y) {
		validate(d, m, y);
		day = d;
		month = m;
		year = y;
	}
	bool isSameDay(const Date& other) const {
		return(day == other.day && month == other.month);
	}
	bool isEqual(const Date& other) const {
		return (day == other.day && month == other.month && year == other.year);
	}
	bool isYesterday(const Date& other) const {
		int d = other.day;
		int m = other.month;
		int y = other.year;
		d++;
		if (d > daysInMonth(m, y)) {
			d = 1;
			m++;
			if (m > 12) {
				m = 1;
				y++;
			}
		}
		return (day == d && month == m && year == y);
	}
	string toString() const {
		return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	}
	void display() const {
		cout << toString();
	}
	int getDay() const { 
		return day;
	}
	int getMonth() const {
		return month;
	}
	int getYear() const { 
		return year;
	}
};
class Entity {
protected:
	string id;
	string name;
	void validateID(const string& id) const {
		if (id.empty())
			throw invalid_argument("ID cannot be empty!");
	}
	void validateName(const string& name) const {
		if (name.empty())
			throw invalid_argument("Name cannot be empty!");
	}
public:
	Entity(string id, string name) {
		validateID(id);
		validateName(name);
		this->id = id;
		this->name = name;
	}
	virtual ~Entity() {}
	string getID() const { 
		return id;
	}
	string getName() const { 
		return name;
	}
	void setID(const string& newID) {
		validateID(newID);
		id = newID;
	}
	void setName(const string& newName) {
		validateName(newName);
		name = newName;
	}
	virtual void display() const = 0;
};
class User :public Entity {
private:
	User** friends;
	int friendCount;
	Page** likedPages;
	int likedCount;
	Post** posts;
	int postCount;
public:
	User(string id, string name) :Entity(id, name) {
		friends = nullptr;
		likedPages = nullptr;
		posts = nullptr;
		friendCount = 0;
		likedCount = 0;
		postCount = 0;
	}
	void addFriend(User* u) {
		for (int i = 0; i < friendCount; i++) {
			if (friends[i] == u)
				return;
		}
		User** temp = new User * [friendCount + 1];
		for (int i = 0; i < friendCount; i++)
			temp[i] = friends[i];
		temp[friendCount] = u;
		delete[] friends;
		friends = temp;
		friendCount++;
	}
	void addPost(Post* p) {
		Post** temp = new Post * [postCount + 1];
		for (int i = 0; i < postCount; i++)
			temp[i] = posts[i];
		temp[postCount] = p;
		delete[] posts;
		posts = temp;
		postCount++;
	}
	void addLikedPage(Page* p) {
		for (int i = 0; i < likedCount; i++) {
			if (likedPages[i] == p)
				return;
		}
		Page** temp = new Page * [likedCount + 1];
		for (int i = 0; i < likedCount; i++)
			temp[i] = likedPages[i];
		temp[likedCount] = p;
		delete[] likedPages;
		likedPages = temp;
		likedCount++;
	}
	void display() const override {
		cout << id << " - " << name << endl;
	}
	~User() {
		delete[] friends;
		delete[] likedPages;
		delete[] posts;
	}
	int getFriendCount() const { 
		return friendCount; 
	}
	User** getFriends() const { 
		return friends;
	}
	int getLikedCount() const { 
		return likedCount;
	}
	Page** getLikedPages() const { 
		return likedPages;
	}
	int getPostCount() const { 
		return postCount;
	}
	Post** getPosts() const { 
		return posts;
	}
};
class SocialNetworkApp {
private:
	User** users;
	int userCount;
	User* currentUser;
	Date currentDate;
public:
	SocialNetworkApp() {
		users = nullptr;
		userCount = 0;
		currentUser = nullptr;
	}
	void addUser(User* u) {
		for (int i = 0; i < userCount; i++) {
			if (users[i]->getID() == u->getID())
				return;
		}
		User** temp = new User * [userCount + 1];
		for (int i = 0; i < userCount; i++)
			temp[i] = users[i];
		temp[userCount] = u;
		delete[] users;
		users = temp;
		userCount++;
	}
	User* findUser(string id) {
		for (int i = 0; i < userCount; i++) {
			if (users[i]->getID() == id)
				return users[i];
		}
		return nullptr;
	}
	void setCurrentUser(string id) {
		User* u = findUser(id);
		if (!u) {
			cout << "User not found!\n";
			return;
		}
		currentUser = u;
		cout << u->getName() << " successfully set as Current User\n";
	}
	void viewFriendList(string id) {
		User* u = findUser(id);
		if (!u) {
			cout << "User not found!\n";
			return;
		}
		cout << "-------------------------------------------------------------------------------------------------------------\n";
		cout << u->getName() << " - Friend List\n\n";
		int count = u->getFriendCount();
		User** friends = u->getFriends();
		if (count == 0) {
	        cout << "No friends found\n";
	        return;
        }
		for (int i = 0; i < count; i++) {
			friends[i]->display();
		}
		cout << "-------------------------------------------------------------------------------------------------------------\n";
		}
	~SocialNetworkApp() {
		for (int i = 0; i < userCount; i++) {
			delete users[i];
		}
		delete[] users;
	}
	void setSystemDate(int d, int m, int y) {
		currentDate = Date(d, m, y);
		cout << "System Date: ";
		currentDate.display();
		cout << endl;
	}
};
// Member 1 code ended
class Activity
{
	int type;
	char* value;
public:
    int getType() { return type; }
    char* getValue() { return value; }
	Activity(int t=0,const char* v=nullptr)
	{
		type=t;
        if (v != nullptr) {
            value = new char[strlen(v) + 1];
            strcpy(value, v);
        }
        else {
            value = nullptr;
        }
	}
    void diplayActivity()
    {
        switch (type) {
        case 1: cout << "is feeling " << value;        break;
        case 2: cout << "is thinking about " << value; break;
        case 3: cout << "is making " << value;         break;
        case 4: cout << "is celebrating " << value;    break;
        }
     }
	 ~Activity()
	 {
		 delete[] value;
}

};
class Comment
{
private:
   
   char *commentId;
   char *postId;
   char *postedBy;
   char *txt;
public:
   Comment(const char*a=nullptr,const char* b = nullptr,const char* c = nullptr,const char* d = nullptr)
   {
       commentId = new char[strlen(a)+1];
       strcpy(commentId, a);
       postId = new char[strlen(b) + 1];
       strcpy(postId, b);
       postedBy = new char[strlen(c) + 1];
       strcpy(postedBy, c);
       txt = new char[strlen(d) + 1];
       strcpy(txt, d);
   }
   char* getcommentId()
   {
       return commentId;
   }
   char* getpostId()
   {
       return postId;
   }
   char* getpostedBy()
   {
       return postedBy;
   }
   char* gettxt()
   {
       return txt;
   }
   void displayComment()
   {
       
       cout <<postedBy << " wrote : \"" << txt <<"\""<< endl;
   }
   ~Comment()
   {
       delete[] commentId;
       delete[] postId;
       delete[] postedBy;
       delete[] txt;
   }
};

class Post {
private:
    
    char* id;
    char* text;
    int day, month, year;
    int postType;//1,2
    Activity* activity;
    char* postedBy;
    char* likedBy[10];       // max 10
    int likedCount;
    Comment* comments[10];   // max 10
    int commentCount;

public:   
    Post(char* pid, char* ptext, int pday, int pmonth, int pyear,
        int ptype, char* ppostedBy, Activity* pact = nullptr)
    {
        id = new char[strlen(pid) + 1];
        strcpy(id, pid);

        text = new char[strlen(ptext) + 1];
        strcpy(text, ptext);

        day = pday;
        month = pmonth;
        year = pyear;
        postType = ptype;

        postedBy = new char[strlen(ppostedBy) + 1];
        strcpy(postedBy, ppostedBy);

        activity = pact;   

        likedCount = 0;
        commentCount = 0;

        for (int i = 0; i < 10; i++) {
            likedBy[i] = nullptr;
            comments[i] = nullptr;
        }
    }
    char* getId()
    {
        return id;
    }
    char* gettext()
    {
        return text;
    }
    int getday()
    {
        return day;
    }
    int getmonth()
    {
        return month;
    }
    int getyear()
    {
        return year;
    }
    int getpostType()
    {
        return postType;
    }
    char* getpostedBy()
    {
        return postedBy;
    }
    char* getlikedBy(int i)
    {
        return likedBy[i];
    }
    Activity *getactivity()
    {
        return activity;
    }
    int getlikedCount() { return likedCount; }
    int getcommentCount() { return commentCount; }
   
    Comment* getcomment(int i) { return comments[i]; }
     
    void addLike(const char* entityId)
    {
        if (likedCount < 10) {
            likedBy[likedCount] = new char[strlen(entityId) + 1];
            strcpy(likedBy[likedCount], entityId);
            likedCount++;
        }
    }
    void addComment(Comment* c)
    {
        if (commentCount < 10)
            comments[commentCount++] = c;
    }
   
 void display()
 {
     
     if (activity != nullptr) {
         cout << postedBy << " ";
         activity->displayActivity();
         cout << endl;
         cout << "     \"" << text << "\"";
     }
     else {
         cout << postedBy << " shared \"" << text << "\"";
     }

     
     cout << " ...(" << day << "/" << month << "/" << year << ")" << endl;

     
     for (int i = 0; i < commentCount; i++)
         comments[i]->displayComment();
 }
    ~Post()
    {
        delete[] id;
        delete[] text;
        delete[] postedBy;
        delete activity;

        for (int i = 0; i < likedCount; i++)
            delete[] likedBy[i];

        for (int i = 0; i < commentCount; i++)
            delete comments[i];
    }
};
//A Memory is a Post having pointer to original post.
class Memory : public Post //inheritance
{
private:
    Post* originalPost;  
    
public:
    Memory(constchar* id,const char* text, int day, int month, int year,const
        char* postedBy, Post* original)
        : Post(id, text, day, month, year,
            original->getpostType(),   
            postedBy,
            nullptr)                   
    {
        originalPost = original;
    }

    Post* getOriginalPost() { return originalPost; }
    void displayMemory()
 {
     cout << "~~~ " << getpostedBy() << " shared a memory ~~~ ...(";
     cout << getday() << "/" << getmonth() << "/" << getyear() << ")" << endl;
     cout << "\"" << gettext() << "\"" << endl;

     int yearDiff = getyear() - originalPost->getyear();
     cout << "(" << yearDiff << " Years Ago)" << endl;

     originalPost->display();
 }
    
    ~Memory() {
        
    }
};

class Page : public Entity {
private:
    Post** posts;
    int postCount;
public:
    Page(string id, string name) : Entity(id, name) {
        posts = nullptr;
        postCount = 0;
    }
    void addPost(Post* p) {
        Post** temp = new Post * [postCount + 1];
        for (int i = 0; i < postCount; i++)
            temp[i] = posts[i];
        temp[postCount] = p;
        delete[] posts;
        posts = temp;
        postCount++;
    }
    void viewPage() {
        cout << "---" << name << "---" << endl;
        for (int i = 0; i < postCount; i++)
            posts[i]->display();
    }
    void display() const override {
        cout << id << " - " << name << endl;
    }
    ~Page() {
        delete[] posts;
    }
};
//functions:
void viewPost(const char* postID, Post** posts, int postCount)

{

    bool found = false;
    for (int i = 0; i < postCount; i++)
    {
        if (strcmp(posts[i]->getId(), postID) == 0)
        {
            posts[i]->display();
            found = true;
            
            break;
        }
    }
    if (!found) cout << "Post not found\n";
}
void likePost(const char* postID, Post** posts,
    int postCount, const char* userID)
{

    for (int i = 0; i < postCount; i++)
    {
        if (strcmp(posts[i]->getId(), postID) == 0)
        {

            for (int j = 0; j < posts[i]->getlikedCount(); j++)
            {
                if (strcmp(posts[i]->getlikedBy(j), userID) == 0)
                {
                    cout << "Already liked!\n";
                    return;
                }
            }

            posts[i]->addLike(userID);
            cout << "Post liked!\n";
            return;
        }
    }
    cout << "Post not found!\n";
}
void seeYourMemories(Post** posts, int postCount,
    const char* currentUserID,
    int sysDay, int sysMonth, int sysYear)
{
    cout << "We hope you enjoy looking back...\n";
    bool found = false;

    for (int i = 0; i < postCount; i++)
    {

        if (strcmp(posts[i]->getpostedBy(), currentUserID) != 0) continue;


        if (posts[i]->getday() == sysDay &&
            posts[i]->getmonth() == sysMonth &&
            posts[i]->getyear() != sysYear)
        {
            int yearDiff = sysYear - posts[i]->getyear();
            cout << "On this Day " << yearDiff << " Years Ago" << endl;
            cout << "---" << endl;
            posts[i]->display();
            found = true;
        }
    }
    if (!found) cout << "No memories found.\n";
}

void viewLikedList(const char* postID, Post** posts, int postCount)
{
    for (int i = 0; i < postCount; i++)
    {
        if (strcmp(posts[i]->getId(), postID) == 0)
        {
            cout << "---------------------------------------" << endl;
            cout << "Post Liked By:" << endl;
            int count = posts[i]->getlikedCount();
            if (count == 0)
                cout << "No likes yet." << endl;
            for (int j = 0; j < count; j++)
                cout << posts[i]->getlikedBy(j) << endl;
            cout << "---------------------------------------" << endl;
            return;
        }
    }
    cout << "Post not found!\n";
}

void postComment(const char* postID, const char* userID,
    const char* text, Post** posts, int postCount)
{
    for (int i = 0; i < postCount; i++)
    {
        if (strcmp(posts[i]->getId(), postID) == 0)
        {
            char newId[20];  strcpy(newId, "cnew");
            Comment* newComment = new Comment("cnew", postID, userID, text);
            posts[i]->addComment(newComment);
            cout << "Comment added!\n";
            return;
        }
    }
    cout << "Post not found!\n";
}
void shareMemory(const char* postID, const char* userID,
    const char* text, Post** posts, int postCount,
    int sysDay, int sysMonth, int sysYear)
{
    for (int i = 0; i < postCount; i++)
    {
        if (strcmp(posts[i]->getId(), postID) == 0)
        {
            Memory* mem = new Memory("mem1", text, sysDay, sysMonth,
                sysYear, userID, posts[i]);
            mem->displayMemory();
            delete mem;
            return;
        }
    }
    cout << "Post not found!\n";
}
int main() {
    
	 //Reading data from Posts.txt
    ifstream fin("Posts.txt");
    if (!fin) {
        cout << "Error! File not found!" << endl;
        return 1;
    }
    else 
        cout << "File Found!" << endl;
    
    int postCount;
    fin >> postCount;
    cout << postCount<<endl;
    Post **posts;
    posts = new Post * [postCount];
    for (int i = 0; i < postCount; i++)
 {
     char tempId[20], temptext[300], tempPostedBy[20];
     int tempDay, tempMonth, tempYear, tempPostType;
     
     fin >> tempPostType >> tempId;
     fin >> tempDay >> tempMonth >> tempYear;
     fin.ignore();
     fin.getline(temptext, 300);
    
     
     Activity* act = nullptr;
     if (tempPostType == 2) {
         char tempActValue[100];
         int tempActType;

         fin >> tempActType;
         fin.ignore();
         fin.getline(tempActValue, 100);

         act = new Activity(tempActType, tempActValue);
     }
     
   
     fin >> tempPostedBy;
     posts[i] = new Post(tempId, temptext, tempDay, tempMonth,
         tempYear, tempPostType, tempPostedBy, act);
     
     char temp[20];
     while (fin >> temp) {
         if (strcmp(temp, "-1") == 0) break;
         posts[i]->addLike(temp);
     }
     
     
    
  
 }
    fin.close();
    
    for (int i = 0; i < postCount; i++)
 {
     cout << posts[i]->getId() << " | "
         << posts[i]->getday() << "/" << posts[i]->getmonth() << "/" << posts[i]->getyear() << " | "
         << posts[i]->gettext() << " | ";

     if (posts[i]->getactivity() != nullptr)
         posts[i]->getactivity()->diplayActivity();

     cout << " | By: " << posts[i]->getpostedBy() << " | Likes: ";

     for (int j = 0; j < posts[i]->getlikedCount(); j++)
         cout << posts[i]->getlikedBy(j) << " ";

     cout << endl;
 }

 //Reading data from Comments.txt

    ifstream in("Comments.txt");
    if (!in) {
        cout << "Error! File not found!" << endl;
        return 1;
    }
    else
        cout << "File Found!" << endl;
    int commentCount;
    in >> commentCount;
    cout << commentCount<<endl;
    Comment** comments;
    comments = new Comment*[commentCount];
    for (int i = 0; i < commentCount; i++) {
     char tempCommentId[20];
     char tempPostId[20];
     char tempPostedBy[20];
     char tempTxt[300];
    
     in >> tempCommentId;
     in >> tempPostId;
     in >> tempPostedBy;
     in.ignore();
     in.getline(tempTxt, sizeof(tempTxt));

    
     comments[i] = new Comment(tempCommentId, tempPostId, tempPostedBy, tempTxt);
 }

   
    in.close();
    for (int i = 0; i < commentCount; i++)
    {
        cout << comments[i]->getcommentId() << " | "
     << comments[i]->getpostId() << " | "
     << comments[i]->getpostedBy() << " | "
     << comments[i]->gettxt() << endl;
    }
	//linking the comment and the post class
for (int i = 0; i < commentCount; i++)
{
    
    for (int j = 0; j < postCount; j++)
    {
        if (strcmp(comments[i]->getpostId(), posts[j]->getId()) == 0)
        {
            posts[j]->addComment(comments[i]);
            break;
        }
    }
}

//Verifyingg
cout << "post1 comments:" << endl;
for (int i = 0; i < posts[0]->getcommentCount(); i++)
    posts[0]->getcomment(i)->displayComment();
 viewPost("post1", posts, postCount);

 viewLikedList("post5", posts, postCount);
 likePost("post5", posts, postCount, "u7");
 viewLikedList("post5", posts, postCount);



 viewPost("post4", posts, postCount);

 seeYourMemories(posts, postCount, "u7", 15, 11, 2017);
 shareMemory("post10", "u7", "Never thought I will be specialist...",
     posts, postCount, 15, 11, 2017);
    
    return 0;
}
