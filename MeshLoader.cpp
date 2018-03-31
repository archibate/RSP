#include "Mesh.h"
#include "MeshNode.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_normalized_axis.hpp>
#include <glm/gtx/norm.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

using std::string;
using std::istringstream;
using std::getline;
using std::ifstream;

static istringstream &operator>>(istringstream &ss, glm::vec3 &v) {
	ss >> v.x >> v.y >> v.z;
	return ss;
}

static istringstream &operator>>(istringstream &ss, glm::quat &q) {
	ss >> q.x >> q.y >> q.z >> q.w;
	return ss;
}

static istringstream &operator>>(istringstream &ss, glm::vec2 &v) {
	ss >> v.x >> v.y;
	return ss;
}

static istringstream &operator>>(istringstream &ss, Vertex &vertex) {
	ss >> vertex.Position >> vertex.Normal >> vertex.TexCoords;
	return ss;
}

static istringstream &operator>>(istringstream &ss, Material &material) {
	string diffuse, specular;
	ss >> diffuse;
	ss >> specular;
	ss >> material.shininess;
	material.diffuse = Texture(diffuse.c_str());
	material.specular = Texture(specular.c_str());
	return ss;
}

/*static string strip(const string &str) {
	return str;
}*/

/*static vector<string> split(const string &str) {
	string::size_type pos = 0;
	vector<string> res;
	while (true) {
		auto beg = str.find_first_not_of(' ', pos);
		if (beg == string::npos)
			break;
		auto end = str.find_first_of(' ', beg);
		auto s = str.substr(beg, end);
		res.push_back(s);
		if (end == string::npos)
			break;
		pos = end;
	}
	return res;
}*/

static vector<string> split(const string &s, const string &seperator = " ") {
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;

  while(i != s.size()){
    //找到字符串中首个不等于分隔符的字母；
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[i] == seperator[x]){
          ++i;
          flag = 0;
          break;
        }
    }

    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[j] == seperator[x]){
          flag = 1;
          break;
        }
      if(flag == 0)
        ++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}

template <typename T>
static T parseStr(const string &str) {
	istringstream ss(str);
	T t;
	ss >> t;
	return t;
}

bool MeshNode::parseNode(ifstream &fin, vector<Mesh *> meshlists)
{
	string line;
	if (!getline(fin, line))
		return false;
	auto words = split(line, "\t");
	if (words.size() == 0)
		return parseNode(fin, meshlists);
	if (words[0] == "end") {
		return false;
	}
	Mesh *mesh = nullptr;
	if (words[0] != "-") {
		unsigned int meshid = parseStr<unsigned int>(words[0]);
		mesh = meshlists[meshid];
	}
	glm::mat4 model;
	if (words[1] == "id") {
		cout << "id" << endl;
	} else if (words[1] == "tr") {
		cout << "tr" << endl;
		auto tr = parseStr<glm::vec3>(words[2]);
		model = glm::translate(model, tr);
	} else if (words[1] == "trsc") {
		cout << "trsc" << endl;
		auto tr = parseStr<glm::vec3>(words[2]);
		auto sc = parseStr<float>(words[3]);
		model = glm::translate(model, tr);
		model = glm::scale(model, glm::vec3(sc, sc, sc));
	} else if (words[1] == "trsv") {
		cout << "trsv" << endl;
		auto tr = parseStr<glm::vec3>(words[2]);
		auto sv = parseStr<glm::vec3>(words[3]);
		model = glm::translate(model, tr);
		model = glm::scale(model, sv);
	} else if (words[1] == "trqa") {
		cout << "trqa" << endl;
		auto tr = parseStr<glm::vec3>(words[2]);
		auto qa = parseStr<glm::quat>(words[3]);
		model = glm::translate(model, tr);
		model = model * glm::toMat4(qa);
		cout << qa.w << ' ' << qa.x << ' ' << qa.y << ' ' << qa.z << endl;
	} else if (words[1] == "trscqa") {
		cout << "trscqa" << endl;
		auto tr = parseStr<glm::vec3>(words[2]);
		auto sc = parseStr<float>(words[3]);
		auto qa = parseStr<glm::quat>(words[4]);
		model = glm::translate(model, tr);
		model = glm::scale(model, glm::vec3(sc, sc, sc));
		model = model * glm::toMat4(qa);
	} else if (words[1] == "trar") {
		cout << "trar" << endl;
		auto tr = parseStr<glm::vec3>(words[2]);
		auto angle = parseStr<float>(words[3]);
		auto axis = parseStr<glm::vec3>(words[4]);
		auto sc = glm::length(axis);
		model = glm::translate(model, tr);
		model = glm::scale(model, glm::vec3(sc, sc, sc));
		model = glm::rotate(model, glm::radians(angle), axis);
	}
	this->mesh = mesh;
	this->trans = model;

	while (true) {
		MeshNode node;
		if (node.parseNode(fin, meshlists))
			this->children.push_back(node);
		else
			break;
	}
	return true;
}

bool MeshNode::parseDefs(ifstream &fin, vector<Mesh *> meshlists)
{
	string line;
	while (true) {
		if (!getline(fin, line))
			return true;
		/*if (line.length() == 0)
			continue;*/
		/*if (line[0] == '#')
			return false;*/

		if (!parseNode(fin, meshlists))
			return true;
	}
}

void MeshNode::fromFile(ifstream &fin)
{
	vector<Mesh *> meshlists;
	string line;
	while (true) {
		if (!getline(fin, line))
			goto end;
inst:
		if (line == "#meshfiles")
			goto meshfiles;
		if (line == "#defs")
			goto defs;
		if (line == "#end")
			goto end;
	}

meshfiles:
	while (true) {
		if (!getline(fin, line))
			goto end;
		if (line.length() == 0)
			continue;
		if (line[0] == '#')
			goto inst;

		istringstream ss(line);
		string filename;
		ss >> filename;
		meshlists.push_back(new Mesh(filename.c_str()));
	}

defs:
	if (!parseDefs(fin, meshlists))
		goto inst;
	else
		goto end;

end:
	/*for (const auto *f: meshlists)
		delete f;*/

	return;
}

void Mesh::fromFile(ifstream &fin)
{
	string line;
	while (true) {
		if (!getline(fin, line))
			goto end;
inst:
		if (line == "#vertices")
			goto vertices;
		if (line == "#indices")
			goto indices;
		if (line == "#material")
			goto material;
		if (line == "#end")
			goto end;
	}

vertices:
	while (true) {
		if (!getline(fin, line))
			goto end;
		if (line.length() == 0)
			continue;
		if (line[0] == '#')
			goto inst;

		istringstream ss(line);
		Vertex vertex;
		ss >> vertex;
		vertices.push_back(vertex);
	}

indices:
	while (true) {
		if (!getline(fin, line))
			goto end;
		if (line.length() == 0)
			continue;
		if (line[0] == '#')
			goto inst;

		istringstream ss(line);
		unsigned int index;
		ss >> index;
		indices.push_back(index);
	}

material:
	do {
		if (!getline(fin, line))
			goto end;
		if (line.length() == 0)
			goto material;
		if (line[0] == '#')
			goto inst;

		istringstream ss(line);
		ss >> material;
	} while (false);

end:
	return;
}
