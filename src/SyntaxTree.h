#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>
#include <vector>
#include <memory>

// Might have to use a larger integer 
/**
 * @brief enum holding uniform characters
 * 
 */
enum class UniformCharacter : int8_t {
    Empty, Idn, Number, Character, CharacterArray, LBracket, RBracket
};


/**
 * @brief most generic class of the tree
 * 
 */
class SyntaxTreeNode {
protected:
    std::vector<std::unique_ptr<SyntaxTreeNode> > m_children;   ///> child nodes

public: 
    virtual bool check() = 0;                                   ///> checks all associated rules

    template<typename T, typename... Args>
    const T* addChild(Args&&... args);
};

/**
 * @brief Leafs of the syntax tree
 * 
 */
class Leaf : public SyntaxTreeNode {
private:
    UniformCharacter m_uniformCharacter = UniformCharacter::Empty;  ///> uniform character
    int m_row = -1;                                                 ///> row in original source file
    std::string m_lexicalUnit = "";                                 ///> actual string read from source

public:
    Leaf() = default;
    Leaf(UniformCharacter uniformCharacter, int row, const std::string &lexicalUnit);

    bool check() override;

    [[nodiscard]] inline UniformCharacter getUniformCharacter() const noexcept { return m_uniformCharacter; }
    [[nodiscard]] inline int getRow() const noexcept { return m_row; }
    [[nodiscard]] inline std::string getLexicalUnit() const noexcept { return m_lexicalUnit; }
};

#endif //SYNTAX_TREE_H