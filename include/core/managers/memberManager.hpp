#ifndef INCLUDE_CORE_MANAGERS_MEMBERMANAGER_HPP_INCLUDED
#define INCLUDE_CORE_MANAGERS_MEMBERMANAGER_HPP_INCLUDED

#include "../sing/member.hpp"
#include <vector>

enum class MEMBER_SEARCH_TYPE { ID, NAME };

class MemberManager {
  private:
	std::vector<Member> members;
	std::string			path;

  public:
	static MemberManager& Instance() {
		static MemberManager inst;
		return inst;
	}
    
	void load(std::string path);
	void save();

	std::vector<Member> getMembers(MEMBER_SEARCH_TYPE s, std::string query);
	void				addMember(const Member& m) { members.push_back(m); }
	void				removeMember(int ID);
	void				editMember(int ID, const Member& m);
};

#endif