#include <string>
#include <vector>


struct preferences{
    std::vector<std::string>positiveIngredients;
    std::vector<std::string>negativeIngredients;
    std::vector<int>negativeIngredientsWeight; // if 0 use default
    std::string foodStylePositive;
    std::string foodStyleNegative;
    std::string regionPositive;
    std::string regionNegative;
    int recipeComplexity; // if -1 user has no preference
    
    preferences(){
        recipeComplexity = -1; 
        foodStylePositive = foodStyleNegative = ""; 
        regionPositive = regionNegative = "";
        
    }
};
