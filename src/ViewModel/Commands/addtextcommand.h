#ifndef ADDTEXTCOMMAND_H
#define ADDTEXTCOMMAND_H
#include "../../Common/BaseCommand.h"
#include "../../Model/Model.h"

class AddTextCommand:public BaseCommand
{
public:
    AddTextCommand(const shared_ptr<Model> &pModel):BaseCommand(pModel){}
    void exec()
    {
        //x,y,TEXT
        vector<string> strings=params.getStrings();
        vector<int> ints=params.getInts();
        pModel->addText(ints[0],ints[1],strings[0]);
    }
};

#endif // ADDTEXTCOMMAND_H
