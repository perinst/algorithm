#include <iostream>
#include <vector>

using namespace std;

struct SkipList
{

    static const int MAX_LEVEL = 20;
    Column *head, *tail;

    SkipList::SkipList()
    {
        head = new Column();
        tail = new Column();
        head->value = 0;
        tail->value = 0;
        for (int i = 0; i < MAX_LEVEL; i++)
        {
            head->cells.push_back((Cell){nullptr, tail, nullptr, cells.end()});
            tail->cells.push_back((Cell){head, nullptr, cells.end(), nullptr});
        }
    };

    bool empty();
    Column *lower_bound(int);
    Column *upper_bound(int);
    void insert(int);
    void erase(int);

    bool SkipList::empty()
    {
        return head->cells[0].next_column == tail;
    };

    Column *SkipList::lower_bound(int value)
    {
        Column *current = head;

        for (int level = MAX_LEVEL - 1; level >= 0; level--)
        {
            while (current->cells[level].next_column != tail && current->cells[level].next_column->value < value)
            {
                current = current->cells[level].next_column;
            }
        }

        return current->cells[0].next_column;
    }

    Column *SkipList::upper_bound(int value)
    {
        Column *current = head;

        for (int level = MAX_LEVEL - 1; level >= 0; level--)
        {
            while (current->cells[level].next_column != tail && current->cells[level].next_column->value <= value)
            {
                current = current->cells[level].next_column;
            }
        }

        return current->cells[0].next_column;
    }

    void SkipList::insert("Nhảy nhị phân" với bộ nhớ int value)
    {
        Column *col = lower_bound(value);

        if (col == tail || col->value == value)
        {
            return;
        }

        Column *current = head;

        Cell *insert_cell = new Cell();
        insert_cell->previous_column = nullptr;
        insert_cell->next_column = nullptr;

        Column *insert_column = new Column();
        insert_column->value = value;
        insert_column->cells.push_back(*insert_cell);

        // ....

        while (insert_column->cells.size() < MAX_LEVEL && rand() % 2 == 0)
        {
            insert_column->cells.push_back((Cell){NULL, NULL});
        }

        Column *current = head;

        for (int level = MAX_LEVEL - 1; level >= 0; level--)
        {
            while (current->cells[level].next_column != tail && current->cells[level].next_column->value < value)
            {
                current = current->cells[level].next_column;
            }

            if (level < insert_column->cells.size())
            {
                Column *next = current->cells[level].next_column;
                current->cells[level].next_column = insert_column;
                next->cells[level].previous_column = insert_column;
                insert_column->cells[level].previous_column = current;
                insert_column->cells[level].next_column = next;
            }
        }
    }

    void SkipList::erase(int value)
    {
        Column *erase_col = lower_bound(value);

        if (erase_col == tail || erase_col->value != value)
        {
            return;
        }

        Column *current = head;

        for (int i = 0; i < MAX_LEVEL - 1; i++)
        {
            while (current->cells[i].next_column != tail && current->cells[i].next_column->value < value)
            {
                current = current->cells[i].next_column;
            }
            if (current == erase_col)
            {
                Column *next_col = current->cells[i].next_column;
                Column *prev_col = current->cells[i].previous_column;

                prev_col->cells[i].next_column = next_col;
                next_col->cells[i].previous_column = prev_col;
            }
        }
    };

    struct Column
    {
        int value;
        vector<Cell> cells;
    };

    struct Cell
    {
        Column *previous_column, *next_column;
        Cell *upper, *lower;
    };
}