/*
    Project: Social Network App
    Course: Object Oriented Programming
    Section: BCS-2F
    Group Leader: Maha Khan 
	Roll No: 25L-0809
    Member 2: Amna Khalid 
	Roll No: 25L-0514
    GitHub: https://github.com/Maha-Khan567/Social-Network-Application
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<fstream>
#include<sstream>
#include <string>
#include<stdexcept>
using namespace std;
// Forward declarations to allow classes to use them cuz used in classes
class Page;
class Post;
class User;
class Comment;
// Member 1 code
// Date class it stores day,month,year and it includes date comparision and validation checks
class Date {
private:
	int day, month, year;
    // Function returns true if year is a leap year
	bool isLeapYear(int y)const {
		return(y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}
    // Returns the number of days in each month
	int daysInMonth(int m, int y) const {
		if (m < 1 || m > 12)
			throw invalid_argument("Invalid month!");
		if (m == 2)
			return isLeapYear(y) ? 29 : 28;
		if (m == 4 || m == 6 || m == 9 || m == 11)
			return 30;
		return 31;
	}
    // Validation for day,month and year
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
    // Returns true if day and month match
	bool isSameDay(const Date& other) const {
		return(day == other.day && month == other.month);
	}
    // Returns true if both dates are exactly the same
	bool isEqual(const Date& other) const {
		return (day == other.day && month == other.month && year == other.year);
	}
    // Returns true if date is yesterday
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
    // Getter functions
	void display() const {
		cout << toString();
	}
    // Mutator Functions
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
// Entity class
// Has pure virtual display()
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
// User class and maintains dynamic arrays of friends, liked pages, and posts
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

// Member 1 code ended
// Function forward declarations
void viewPost(const char*, Post**, int);
void likePost(const char*, Post**, int, const char*);
void seeYourMemories(Post**, int, const char*, int, int, int);
void viewLikedList(const char*, Post**, int);
void postComment(const char*, const char*, const char*, Post**, int);
void shareMemory(const char*, const char*, const char*, Post**, int, int, int, int);
//Activity class used to diplay activity in posts of type 2 
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
    void displayActivity()
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
//Comment class used to display comments
class Comment
{
private:
   
   char *commentId;
   char *postId;
   char *postedBy;
   char *txt;
public:
   Comment(const char*a=nullptr,const char* b = nullptr,const char* c = nullptr,const char* d = nullptr)
   {   commentId = postId = postedBy = txt = nullptr;
	   if (a) {
       commentId = new char[strlen(a)+1];
       strcpy(commentId, a);}
	if (b) {
       postId = new char[strlen(b) + 1];
       strcpy(postId, b);}
	if (c) {
       postedBy = new char[strlen(c) + 1];
       strcpy(postedBy, c);}
	if (d) {
       txt = new char[strlen(d) + 1];
       strcpy(txt, d);}
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
//Post class used to like comment and display a post
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
    Post(const char* pid,const char* ptext, int pday, int pmonth, int pyear, int ptype,const char* ppostedBy, Activity* pact = nullptr)
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
    int getlikedCount() { 
		return likedCount;
	}
    int getcommentCount() { 
		return commentCount; 
	}
   
    Comment* getcomment(int i) { 
		return comments[i];
	}
     
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
//Memory class helps in displaying memories
class Memory : public Post //inheritance
{
private:
    Post* originalPost;  
    
public:
    Memory(const char* id,const char* text, int day, int month, int year,const char* postedBy, Post* original) : Post(id, text, day, month, year, original->getpostType(),postedBy,nullptr)                   
    {
        originalPost = original;
    }

    Post* getOriginalPost() { 
		return originalPost;
	}
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
//Page class is used to view page,post,and liked list 
//add posts,like post,see memories,share memory,post comment
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
 Post** getPosts() { 
	 return posts;
 }
 int getPostCount() { 
	 return postCount;
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
void likePost(const char* postID, Post** posts, int postCount, const char* userID)
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
void seeYourMemories(Post** posts, int postCount, const char* currentUserID, int sysDay, int sysMonth, int sysYear)
{
    cout << "We hope you enjoy looking back...\n";
    bool found = false;

    for (int i = 0; i < postCount; i++)
    {

        if (strcmp(posts[i]->getpostedBy(), currentUserID) != 0) 
			continue;

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
    if (!found) 
		cout << "No memories found.\n";
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

void postComment(const char* postID, const char* userID, const char* text, Post** posts, int postCount)
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
void shareMemory(const char* postID, const char* userID,const char* text, Post** posts, int postCount,int sysDay, int sysMonth, int sysYear)
{
    for (int i = 0; i < postCount; i++)
    {
        if (strcmp(posts[i]->getId(), postID) == 0)
        {
            Memory* mem = new Memory("mem1", text, sysDay, sysMonth, sysYear, userID, posts[i]);
            mem->displayMemory();
            delete mem;
            return;
        }
    }
    cout << "Post not found!\n";
}
// SocialNetworkApp the main driver class
class SocialNetworkApp {
private:
	User** users;
	int userCount;
	User* currentUser;
	Date currentDate;
	Page** pages;
	int pageCount;
	Post** posts;
	int postCount;
	Comment** comments;
	int commentCount;
public:
SocialNetworkApp() {
    users = nullptr;
    userCount = 0;
    currentUser = nullptr;
    pages = nullptr;
    pageCount = 0;
    posts = nullptr;
    postCount = 0;
    comments = nullptr;
    commentCount = 0;
}
// Adds a user to the app
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
    // Finds and returns a User by ID
	User* findUser(string id) {
		for (int i = 0; i < userCount; i++) {
			if (users[i]->getID() == id)
				return users[i];
		}
		return nullptr;
	}
    // Sets the active user by ID
	void setCurrentUser(string id) {
		User* u = findUser(id);
		if (!u) {
			cout << "User not found!\n";
			return;
		}
		currentUser = u;
		cout << u->getName() << " successfully set as Current User\n";
	}
    // Displays the full friend list of the user
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
// Displays posts from friends and liked pages posted today or yesterday
void viewHome() {
	if (!currentUser) {
		cout << "No current user.\n";
		return;
	}
	cout << "---- Home ----\n";
	User** friends = currentUser->getFriends();
	int friendCount = currentUser->getFriendCount();
	for (int i = 0; i < friendCount; i++) {
		if (!friends[i]) 
			continue;
		Post** posts = friends[i]->getPosts();
		int postCount = friends[i]->getPostCount();
		if (!posts) 
			continue;
		for (int j = 0; j < postCount; j++) {
			if (!posts[j]) 
				continue;
			Date postDate(posts[j]->getday(),posts[j]->getmonth(),posts[j]->getyear());
			if (postDate.isEqual(currentDate) || currentDate.isYesterday(postDate)) {
				posts[j]->display();
				cout << endl;
			}
		}
	}
	Page** pages = currentUser->getLikedPages();
	int pageCount = currentUser->getLikedCount();
	for (int i = 0; i < pageCount; i++) {
		if (!pages[i]) 
			continue;
		Post** posts = pages[i]->getPosts();
		int postCount = pages[i]->getPostCount();
		if (!posts) 
			continue;
		for (int j = 0; j < postCount; j++) {
			if (!posts[j]) 
				continue;
			Date postDate(posts[j]->getday(),
				posts[j]->getmonth(),
				posts[j]->getyear());
			if (postDate.isEqual(currentDate) ||
				currentDate.isYesterday(postDate)) {
				posts[j]->display();
				cout << endl;
			}
		}
	}
}
// Main menu loop
void Run() {
    int choice;
    string id, text;
    do {
        cout << "\n1. Set Current User\n";
        cout << "2. View Friend List\n";
        cout << "3. View Profile\n";
        cout << "4. View Home\n";
        cout << "5. View Post\n";
        cout << "6. Like Post\n";
        cout << "7. Post Comment\n";
        cout << "8. View Liked List\n";
        cout << "9. See Your Memories\n";
        cout << "10. Share Memory\n";
		cout << "11. View Page\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
        case 1: 
			cout << "Enter User ID: ";
			cin >> id; 
			setCurrentUser(id);
			break;
        case 2: 
			cout << "Enter User ID: "; 
			cin >> id; 
			viewFriendList(id);
			break;
        case 3:
			viewProfile();
			break;
        case 4:
			viewHome();
			break;
        case 5:
			cout << "Enter Post ID: ";
			cin >> id;
            viewPost(id.c_str(), posts, postCount);
			break;
        case 6:
			if (!currentUser) { 
			cout << "Set a user first.\n"; 
			break;
		}
              cout << "Enter Post ID: ";
			cin >> id;
              likePost(id.c_str(), posts, postCount, currentUser->getID().c_str());
			break;
        case 7: if (!currentUser) 
		{ 
			cout << "Set a user first.\n"; 
			break;
		}
              cout << "Enter Post ID: ";
			cin >> id;
              cout << "Enter comment: ";
			cin.ignore(); getline(cin, text);
              postComment(id.c_str(), currentUser->getID().c_str(), text.c_str(), posts, postCount); 
			break;
        case 8: 
			cout << "Enter Post ID: ";
			cin >> id;
            viewLikedList(id.c_str(), posts, postCount); 
			break;
        case 9: if (!currentUser)
		{ 
			cout << "Set a user first.\n";
			break; 
		}
              seeYourMemories(posts, postCount, currentUser->getID().c_str(), currentDate.getDay(), currentDate.getMonth(), currentDate.getYear()); 
			break;
        case 10: if (!currentUser) {
			cout << "Set a user first.\n"; 
			break;
		}
		case 11:
        cout << "Enter Page ID: ";
          cin >> id;
        {
        Page* p = findPage(id);
        if (p) p->viewPage();
        else cout << "Page not found!\n";
         }
          break;
               cout << "Enter Post ID to share as memory: ";
			cin >> id;
               cout << "Enter memory text: "; 
			cin.ignore(); 
			getline(cin, text);
               shareMemory(id.c_str(), currentUser->getID().c_str(), text.c_str(), posts, postCount, currentDate.getDay(), currentDate.getMonth(), currentDate.getYear()); 
			break;
        }
    } while (choice != 0);
}
~SocialNetworkApp() {
    
    delete[] comments;
    for (int i = 0; i < postCount; i++)
		delete posts[i];
    delete[] posts;
    for (int i = 0; i < pageCount; i++) 
		delete pages[i];
    delete[] pages;
    for (int i = 0; i < userCount; i++) 
		delete users[i];
    delete[] users;
}
// Sets the system date used to filter home feed and detect memories
	   void setSystemDate(int d, int m, int y) {
		   currentDate = Date(d, m, y);
		   cout << "System Date: ";
		   currentDate.display();
		   cout << endl;
	  }
      void viewProfile() {
	       if (!currentUser) {
		   cout << "No current user.\n";
		   return;
	   }
	   cout << "---- " << currentUser->getName() << " Profile ----\n";
	   Post** posts = currentUser->getPosts();
	   int count = currentUser->getPostCount();
	   if (count == 0) {
		   cout << "No posts to show.\n";
		   return;
	   }
	   for (int i = 0; i < count; i++) {
		   posts[i]->display();
		   cout << endl;
	   }
       }
// Adds a page
void addPage(Page* p) {
    Page** temp = new Page * [pageCount + 1];
    for (int i = 0; i < pageCount; i++) temp[i] = pages[i];
    temp[pageCount] = p;
    delete[] pages;
    pages = temp;
    pageCount++;
}
// Finds and returns a Page by ID
Page* findPage(string id) {
    for (int i = 0; i < pageCount; i++)
        if (pages[i]->getID() == id)
            return pages[i];
    return nullptr;
}
// Loads all data from Pages.txt, Posts.txt, Comments.txt, and Users.txt
// Links comments to their posts, then calls loadUsers() and linkPostsToOwners()
void loadFromFiles() {
    // Load Pages
    ifstream pgFile("Pages.txt");
    int pgCount;
    pgFile >> pgCount;
    pages = new Page * [pgCount];
    pageCount = 0;
    string pgId, pgName;
    pgFile.ignore();
    for (int i = 0; i < pgCount; i++) {
        pgFile >> pgId;
        pgFile.ignore();
        getline(pgFile, pgName);
        pages[pageCount++] = new Page(pgId, pgName);
    }
    pgFile.close();
    // Load Posts
    ifstream postFile("Posts.txt");
    int pCount;
    postFile >> pCount;
    posts = new Post * [pCount];
    postCount = 0;
    for (int i = 0; i < pCount; i++) {
        char pId[20];
		char pText[300];
		char pPostedBy[20];
        int pDay, pMonth, pYear, pType;
        postFile >> pType >> pId ;
		postFile>> pDay >> pMonth >> pYear;
        postFile.ignore();
        postFile.getline(pText, 300);
        Activity* act = nullptr;
        if (pType == 2) {
            char actVal[100];
            int actType;
            postFile >> actType;
            postFile.ignore();
            postFile.getline(actVal, 100);
            act = new Activity(actType, actVal);
        }
        postFile >> pPostedBy;
        posts[postCount] = new Post(pId, pText, pDay, pMonth, pYear, pType, pPostedBy, act);
        char likeToken[20];
        while (postFile >> likeToken) {
            if (strcmp(likeToken, "-1") == 0) break;
            posts[postCount]->addLike(likeToken);
        }
        postCount++;
    }
    postFile.close();
    // Load Comments
    ifstream cmtFile("Comments.txt");
    int cCount;
    cmtFile >> cCount;
    comments = new Comment * [cCount];
    commentCount = 0;
    for (int i = 0; i < cCount; i++) {
        char cId[20];
		char cPostId[20];
		char cPostedBy[20];
		char cTxt[300];
        cmtFile >> cId >> cPostId >> cPostedBy;
        cmtFile.ignore();
        cmtFile.getline(cTxt, 300);
        comments[commentCount++] = new Comment(cId, cPostId, cPostedBy, cTxt);
    }
    cmtFile.close();
    // Link comments to posts
    for (int i = 0; i < commentCount; i++)
        for (int j = 0; j < postCount; j++)
            if (strcmp(comments[i]->getpostId(), posts[j]->getId()) == 0) {
                posts[j]->addComment(comments[i]);
                break;
            }

    loadUsers();
    linkPostsToOwners();
}
void loadUsers() {
    ifstream userFile("Users.txt");
    int uCount;
    userFile >> uCount;
    userFile.ignore();
    string userLines[20];
    for (int i = 0; i < uCount; i++)
        getline(userFile, userLines[i]);
    userFile.close();
    // users created
    for (int i = 0; i < uCount; i++) {
        istringstream ss(userLines[i]);
        string uId, token, uName;
        ss >> uId;
        uName = "";
        while (ss >> token) {
            if (token == "-1" || (token[0] == 'u' && isdigit(token[1])) || (token[0] == 'p' && isdigit(token[1])))
                break;
            if (!uName.empty()) uName += " ";
            uName += token;
        }
        addUser(new User(uId, uName));
    }
    // linked friends and liked pages
    for (int i = 0; i < uCount; i++) {
        istringstream ss(userLines[i]);
        string uId, token;
        ss >> uId;
        User* u = findUser(uId);
        // skip tokens names
        while (ss >> token) {
            if (token == "-1" || (token[0] == 'u' && isdigit(token[1])) || (token[0] == 'p' && isdigit(token[1])))
                break;
        }
        while (token != "-1") {
            User* friendUser = findUser(token);
            if (friendUser)
				u->addFriend(friendUser);
            if (!(ss >> token)) 
				break;
        }
        while (ss >> token && token != "-1") {
            Page* likedPage = findPage(token);
            if (likedPage) 
				u->addLikedPage(likedPage);
        }
    }
}
void linkPostsToOwners() {
    for (int i = 0; i < postCount; i++) {
        string ownerID = string(posts[i]->getpostedBy());
        User* ownerUser = findUser(ownerID);
        if (ownerUser) 
		{ 
			ownerUser->addPost(posts[i]);
						continue; 
		}
        Page* ownerPage = findPage(ownerID);
        if (ownerPage) 
			ownerPage->addPost(posts[i]);
    }
}
};
int main() {
	// all implementation in one go
    SocialNetworkApp app;
    app.loadFromFiles();
    app.setSystemDate(14, 11, 2017);
    app.Run();
    return 0;
}
