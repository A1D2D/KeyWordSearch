#include <iostream>
#include "KeyWordSearch.h"

//* This is a test class for KeyWordSearch witch can find keywords in a large text
//* There are also options to set case sensitivity ,and checks for keyword starting the sentence / keyword
//* The example searches through the story and counts how many keywords was found in the text

std::string storyAboutADuck = R"(
   Once upon a time, in a peaceful countryside surrounded by rolling hills and meandering rivers, there was a quaint
   little village named Quackington. Nestled in the heart of this village was a small yet charming farm
   owned by a kind-hearted farmer named Mr. Higgins. The farm was a haven for various animals, from chickens and cows
   to goats and a few friendly sheep. Among these animals lived a very special duck named Daisy.
   Daisy was not just any ordinary duck. She had bright, intelligent eyes that sparkled with curiosity and an
   adventurous spirit that set her apart from the other ducks in the pond. Daisy loved exploring new places and
   discovering exciting things, and she always dreamed of swimming in a pool. The idea of a pool, with its clear,
   still waters and the scent of chlorine, fascinated her. She had overheard the farmer’s grandchildren talking
   about their trips to the local swimming pool, and since then, it had become her dream to experience it for herself.
   One warm summer day, as the sun cast a golden glow over Quackington, Daisy waddled around the farm,
   her mind filled with thoughts of the elusive pool. She had already swum in the pond countless times,
   navigating through reeds and lily pads, and now she yearned for something different.
   Little did she know, her chance was about to come sooner than she expected.
   That afternoon, Mr. Higgins decided to take a break from his work and head into town to run some errands.
   His grandchildren, Emma and Jack, were visiting for the summer, and they begged their grandfather to
   take them to the community pool. Knowing how much his grandchildren loved swimming, Mr.
   Higgins agreed, and soon they were on their way. As they prepared to leave, Daisy watched with keen interest.
   She noticed the children packing towels, swimsuits, and a colorful beach ball. Her curiosity was piqued.
   “This must be the day I finally get to see the pool,” Daisy thought to herself.
   As Mr. Higgins and the children climbed into the old, red pickup truck, Daisy made a bold decision.
   She waddled quickly and quietly towards the truck, flapping her wings for balance. With a quick hop,
   she managed to sneak into the back of the truck, hiding behind a stack of hay bales. No one noticed her presence
   as the truck rumbled to life and set off down the bumpy dirt road. The journey to the community pool seemed to take
   forever, but Daisy’s excitement kept her awake and alert. She peeked out from behind the hay bales, her heart racing
   as they neared the town. Finally, the truck pulled into the parking lot of the pool. The sound of children laughing
   and splashing echoed through the air, making Daisy’s heart leap with joy. Emma and Jack were the first to jump out
   of the truck, racing towards the entrance with their towels flapping behind them. Mr. Higgins followed, carrying a
   large picnic basket filled with sandwiches, fruits, and lemonade. Daisy waited until they were out of sight before
   making her move. She cautiously climbed out of the truck, looking around to make sure no one was watching.
   The pool was even more magnificent than Daisy had imagined. It was large and rectangular, with sparkling blue water
   that glistened under the sun. Colorful umbrellas dotted the poolside, and children of all ages played in the shallow
   end, their laughter filling the air. There were diving boards, slides, and even a small fountain that sprayed water
   into the air, creating a mesmerizing rainbow in the mist. Daisy’s webbed feet pitter-pattered across the hot pavement
   as she made her way to the pool. She approached the edge, her reflection shimmering in the clear water.
   Taking a deep breath, she hopped in. The sensation was unlike anything Daisy had ever felt. The water was cool and
   refreshing, enveloping her in a gentle embrace. It was much deeper than the pond back home, and she reveled in the
   freedom to dive and swim without the hindrance of reeds or mud. She paddled around, experimenting with the different
   depths, and soon found herself at the deep end where the diving boards were located. Intrigued by the sight of
   children jumping off the boards and making spectacular splashes, Daisy decided to try it herself. She paddled to the
   pool's edge, waddled up the steps, and found herself at the base of the diving board. It was much higher than it
   looked from the water, but Daisy’s adventurous spirit urged her on. With a little hop, she made her way up the board,
   her heart pounding with excitement and a touch of fear. When she reached the end of the board, Daisy looked down at
   the water below. It seemed much farther away now. She hesitated for a moment, then took a deep breath, closed her eyes,
   and jumped. The sensation of falling through the air was exhilarating, and when she hit the water, it enveloped her
   in a cool splash. She resurfaced, quacking in delight, and was met with applause and laughter from the children watching.
   For the rest of the afternoon, Daisy swam and played in the pool, joining in with the children’s games and
   making new friends. She even got a chance to go down the slide, which she found to be just as thrilling as the diving board.
   Mr. Higgins and his grandchildren noticed the little duck enjoying herself but decided to let her be, enjoying the
   sight of Daisy’s evident happiness. As the sun began to set, casting a golden glow over the pool, Daisy knew it was
   time to head back to the farm. Reluctantly, she climbed out of the pool, shaking off the water from her feathers.
   She waddled back to the truck, hiding behind the hay bales once more, and waited for Mr.
   Higgins and the children to finish packing up. The journey back to the farm was peaceful, with Daisy feeling a sense
   of contentment and fulfillment. She had finally experienced the joy of swimming in a pool, and it had been everything
   she dreamed of and more. When they arrived back at the farm, Daisy hopped out of the truck and made her way
   back to the pond, where her friends were waiting. As she settled down for the night, Daisy couldn’t help but smile
   to herself. She knew she would always cherish the memories of that special day. From then on, whenever the farmer’s
   grandchildren visited, they made sure to take Daisy along to the pool, knowing how much it meant to her. And so,
   Daisy the duck lived happily ever after, her adventurous spirit leading her to new and exciting experiences,
   but none as memorable as her first swim in the pool.
)";

int main() {
   std::vector<std::string> keyWords = {"the","once",",","duck"};
   std::vector<int> count(keyWords.size(),0);

   StringUtils::KeyWordSearch keyWordSearch;
   for (const auto & keyWord : keyWords) {
      if(keyWord == "the") {
         keyWordSearch.addKeyWord(keyWord,false,false);
      } else keyWordSearch.addKeyWord(keyWord,true,false);
   }

   std::vector<StringUtils::KeyWordSearch::MatchDetail> keywordsArray = keyWordSearch.findKeywords(storyAboutADuck);
   for (const auto& item : keywordsArray) {
      count[item.id]++;
   }

   for (int i = 0; i < keyWords.size(); ++i) {
      std::cout << "found: " << count[i] << " matches of: " << keyWords[i] << std::endl;
   }
   return 0;
}
