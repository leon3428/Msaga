import json

def readFile(filename):
    ret = []

    with open(filename, "r") as f:
        for line in f:
            ret += line.split(' ')

    return [x.strip(' \n') for x in ret]


def createIndex(characters, nodeTypes):
    index = {}
    reverseIndex = {}

    for ch in characters:
        found = False

        while not found:
            print('[', ch, ']: ', end='')
            nodeType = input().strip(' \n')
            found = nodeType in nodeTypes
        
        index[ch] = nodeType
        reverseIndex[nodeType] = ch

    with open('index.json', 'w') as f:
        f.write(json.dumps((index, reverseIndex)))

def writecpp(characters, nodeTypes):
    with open('index.json', 'r') as f_json, open('Serialization.cpp', 'w') as f_dst:
        index, reverseIndex = json.loads(f_json.read())

        f_dst.write('std::string Msaga::NodeTypeToString(NodeType nt) {\n')
        for nodeType in nodeTypes:
            f_dst.write('\tif(nt == NodeType::' + nodeType + ')\n')
            f_dst.write('\t\treturn "' + reverseIndex[nodeType] + '";\n')

        f_dst.write('\treturn "error";\n')
        f_dst.write('}')
        f_dst.write('\n\n')

        # f_dst.write('NodeType Msaga::StringToNodeType(const std::string &s) {\n')
        # for ch in characters:
        #     f_dst.write('\tif(s == "' + ch + '")\n')
        #     f_dst.write('\t\treturn NodeType::' + index[ch] + ';\n')

        # f_dst.write('\treturn NodeType::Error;\n')
        # f_dst.write('}')

        f_dst.write('SyntaxTreeNode* Msaga::constructInnerNode(const std::string &s, SyntaxTreeNode *parent){\n')
        for ch in characters:
            if ch[0] == "<":
                f_dst.write('\tif(s == "' + ch + '")\n')
                f_dst.write('\t\treturn parent -> addChild<' + index[ch] + '>();\n')
        f_dst.write('\treturn nullptr;\n')
        f_dst.write('}')

        f_dst.write('\n\n')

        f_dst.write('SyntaxTreeNode* Msaga::constructLeafNode(const std::string &s, int row, const std::string &lexicalUnit, SyntaxTreeNode *parent){\n')
        for ch in characters:
            if ch[0] != "<":
                f_dst.write('\tif(s == "' + ch + '")\n')
                f_dst.write('\t\treturn parent -> addChild<' + index[ch] + '>(row, lexicalUnit);\n')
        f_dst.write('\treturn nullptr;\n')
        f_dst.write('}')

        f_dst.write('\n\n')

        f_dst.write('bool Msaga::isLeaf(NodeType nt) {\n')
        for nodeType in nodeTypes:
            if nodeType[:4] == "Leaf":
                f_dst.write('\tif(nt == NodeType::' + nodeType + ')\n')
                f_dst.write('\t\treturn true;\n')

        f_dst.write('\treturn false;\n')
        f_dst.write('}')


def main():
    characters = readFile('characters.txt')
    nodeTypes = readFile('nodeTypes.txt')

    if len(characters) != len(nodeTypes):
        print('[WARN]: different amount of characters and node types (', len(characters), '-', len(nodeTypes), ')')

    writecpp(characters, nodeTypes)

if __name__ == '__main__':
    main()