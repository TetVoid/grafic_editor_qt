#include "figure_memory.h"


FigureMemory::FigureMemory()
{

}

FigureMemory::~FigureMemory()
{

}

Figure* FigureMemory::operator[](int index)
{

    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (int i = 0; i != index; i++)
        it++;

	return it->second;
}

int  FigureMemory::size()
{
    return figure_list.size();
}

void FigureMemory::add(Figure* figure,int index)
{
    if(figure!=NULL)
	figure_list[index] = figure;
}

void FigureMemory::del()
{
    if (figure_index != -1)
    {
        std::map <int, Figure*> ::iterator delete_el;
        delete_el = figure_list.find(figure_index);
        figure_list.erase(delete_el);
        figure_index = -1;
    }
}

void FigureMemory::del(int index)
{
    std::map <int, Figure*> ::iterator delete_el;
    delete_el = figure_list.find(index);
    figure_list.erase(delete_el);
    figure_index = -1;
}

void FigureMemory:: move(QPointF pt)
{
    if (figure_index != -1)
    figure_list[figure_index]->move(pt);
}




void  FigureMemory::select(QPointF pt)
{
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    bool selected = false;
    for (; it != figure_list.end(); it++)
    {
      
        int prev_index = figure_index;
        if (it->second->select(pt))
        {
            if (figure_index != -1 && figure_index != it->first)
                figure_list[figure_index]->stop_select();
            figure_index = it->first;
            selected = true;
           
        }
        else if (figure_index == it->first)
            figure_index = -1;

       
    }
    if (!selected)
        figure_index = -1;
}


void FigureMemory::draw(QPainter* painter)
{
    
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
    {
        it->second->draw(painter);
    }
}


bool FigureMemory::is_selected()
{
    if (figure_index == -1)
        return false;
    else
        return true;
}

bool FigureMemory::check_id(int id)
{
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
        if (it->first == id)
            return false;

    return true;
}

void FigureMemory::save(std::wstring path)
{
    std::wstring save_string=L"";
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
        save_string += it->second->save()+L"\n";
    if(path.find(L".gef")==-1)
        path += L".gef";
    std::wofstream fout(path, std::ios::app);
    fout << save_string;
    fout.close();
}

void  FigureMemory::load(std::wstring path)
{
    std::wstring string;
    std::vector< std::wstring> load_vector;
    std::wifstream file(path);
    int index = 0;
    int figur_number = 0;
    while (getline(file, string))
    {
        load_vector.push_back(string);
        index++;
        if (index == 4)
        {
            Figure* pict = NULL;
            if (load_vector[0]._Equal(L"Elipse"))
                pict = new Elipse(load_vector);
            else if (load_vector[0]._Equal(L"Rectangle"))
                pict = new Rectangle(load_vector);
            else if (load_vector[0]._Equal(L"Triangle"))
                pict = new Triangle(load_vector);
            else if (load_vector[0]._Equal(L"Arrow"))
            {
                std::vector<std::wstring> figInfo1 = split(load_vector[1]);
                std::vector<std::wstring> figInfo2 = split(load_vector[2]);
                QPointF pt1(std::stoi(figInfo1[0]), std::stoi(figInfo1[1]));
                QPointF pt2(std::stoi(figInfo2[0]), std::stoi(figInfo2[1]));
                Figure* fig1 = get_by_cords(pt1);
                Figure* fig2 = get_by_cords(pt2);
                pict = new Arrow(fig1,fig2);
            }

            figure_list[figur_number] = pict;
            figur_number++;

            index = 0;
            load_vector.clear();      
        }
    }
}

void FigureMemory::clear()
{
    figure_list.clear();
}

Figure* FigureMemory::get_by_cords(QPointF pt)
{
    Figure* answer = NULL;
    std::map <int, Figure*> ::iterator it = figure_list.begin();
    for (; it != figure_list.end(); it++)
        if (it->second->check_position( pt))
        {
            answer = it->second;
            break;
        }
    return answer;
}

std::vector<std::wstring> FigureMemory::split(std::wstring str)
{
    std::wstring temp;
    std::vector<std::wstring> parts;
    std::wstringstream wss(str);
    while (std::getline(wss, temp, L' '))
        parts.push_back(temp);

    return parts;
}