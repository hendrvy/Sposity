#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <vector>
#include <string>
#include <random>
#include <numeric>     
#include <ctime>     
#include <sstream>     
#include <iomanip>     
#include <algorithm>   
#include <iostream>
#include <fstream>     

using namespace std;
using namespace sf;

// --- Enumerasi Status Aplikasi ---
enum class AppState { Home, Player };
enum class HomeSubState { BrowseSongs, ViewHistory, ViewQueue, ViewPlaylists, CreateNewPlaylist, ViewPlaylistContent };

// --- Struktur Data Lagu ---
struct Song {
    string title;
    string artist;
    string audioFile;
    string coverFile;
    string thumbnailFile;
    vector<pair<float, string>> syncedLyrics;
};

// --- Struktur Data Playlist ---
struct Playlist {
    string name;
    vector<int> songIndices; // Menyimpan indeks lagu dari 'library'
};


// --- Library Lagu (Data Contoh) ---
vector<Song> library = {
    {"About You", "The 1975", "assets/songs/aboutyouu.wav", "assets/covers/aboutyou.png", "assets/covers/aboutyou.png",
        {
            {0.0f, ""},
            {44.5f, "I know a place"},
            {54.0f, "It's somewhere I go"},
            {57.0f, "When i need to remember your face"},
            {64.0f, "We get married"},
            {69.0f, "In Our Head"},
            {74.0f, "Something to do"},
            {76.0f, "While we try to recall"},
            {79.0f, "How we meet"},
            {84.0f, "Do you think I have forgotten?"},
            {89.0f, "Do you think I have forgotten?"},
            {94.0f, "Do you think I have forgotten"},
            {99.0f, "About You"},
            {104.0f, "You and I (don't let go)"},
            {108.5f, "We're alive (don't let go)"},
            {114.0f, "With nothing to do"},
            {116.0f, "I could lay and just look in your eyes"},
            {124.0f, "Wait (don't let go)"},
            {129.0f, "and pretend (don't let go)"},
            {134.0f, "Hold on and hope"},
            {136.0f, "that we'll find our way back in the end"},
            {141.0f, "(in the end)"},
            {144.0f, "Do you think I have forgotten?"},
            {149.0f, "Do you think I have forgotten?"},
            {153.5f, "Do you think I have forgotten"},
            {159.0f, "About you"},
            {164.0f, "Do you think I have forgotten?"},
            {169.0f, "Do you think I have forgotten?"},
            {173.0f, "Do you think I have forgotten"},
            {179.0f, "About you"},
            {184.0f, "And there was something 'bout you"},
            {186.0f, "that now I can't remember"},
            {191.5f, "that made my heart surrender"},
            {194.0f, "And I miss you on a train,"},
            {197.0f, "I miss you in the morning"},
            {199.0f, "I never know what to think about"},
            {203.0f, "I think about you (so don't let go)"},
            {209.0f, "About you (so don't let go)"},
            {214.0f, "Do you think I have forgotten"},
            {219.0f, "about you? (Don't let go)"},
            {224.0f, "About you"},
            {229.0f, "About you"},
            {234.0f, "Do you think I have forgotten"},
            {239.0f, "About you? (Don't let go)"},
            {244.0f, ""}
        }},

    {"Best Part", "Daniel Caesar ft. HER", "assets/songs/bestpart.wav", "assets/covers/bestpart.png", "assets/covers/bestpart.png",
        {
            {6.0f, "Ooooh, hey"},
            {14.0f, "you don't know babe"},
            {17.0f, "When you hold me"},
            {20.0f, "And kiss me slowly"},
            {22.5f, "It's the sweetest thing"},
            {27.0f, "And it don't change, if i had it my way"},
            {33.5f, "You would know that you are"},
            {39.0f, "You're the coffee that i need in the morning"},
            {42.5f, "You're my sunshine"},
            {43.5f, "In the rain when it's pouring"},
            {45.5f, "Won't you give yourself to me"},
            {47.0f, "Give it all, oh"},
            {51.0f, "I just wanna see"},
            {52.5f, "I just wanna see how beautiful you are"},
            {59.0f, "You know that i see it"},
            {62.0f, "I know you're a star"},
            {65.0f, "Where you go i'll follow"},
            {69.5f, "No matter how far"},
            {72.0f, "If life is a movie"},
            {75.0f, "Oh you're the best part, oh"},
            {82.0f, "You're the best part, ooh"},
            {89.0f, "Best part"},
            {91.0f, "It's this sunrise, and those brown eyes, yes"},
            {97.8f, "You're the one that i desire"},
            {104.0f, "When we wake up"},
            {107.0f, "And then we make love (make love)"},
            {110.0f, "It makes me feel so nice"},
            {115.8f, "You're my water when i'm stuck in the desert"},
            {119.1f, "You're the tylenol i take when my head hurts"},
            {123.0f, "You're the sunshine on my life"},
            {129.0f, "I just wanna see how beautiful you are"},
            {136.0f, "You know that i see it"},
            {139.0f, "I know you're a star"},
            {142.0f, "Where you go i'll follow"},
            {145.0f, "No matter how far"},
            {148.8f, "If life is a movie"},
            {152.0f, "Then you're the best part, oh"},
            {158.5f, "You're the best part, ooh Best part"},
            {167.0f, "If you love me, won't you say something?"},
            {170.0f, "If you love, wont you wont you?"},
            {173.0f, "If you love me, won't you say something?"},
            {176.8f, "If you love me, won't you"},
            {178.8f, "Love me, won't you?"},
            {180.0f, "If you love me, won't you say something?"},
            {183.0f, "If you love me, won't you?"},
            {186.0f, "If you love me, won't you say something?"},
            {189.2f, "If you love me, won't you"},
            {191.0f, "Love me, won't you?"},
            {193.0f, "If you love me, won't you say something?"},
            {196.0f, "If you love me, won't you?"},
            {199.0f, "If you love me, won't you say something?"},
            {202.0f, "If you love me, won't you"},
            {204.0f, "Love me, won't you?"}
        }},

    {"Birds Of A Feather", "Billie Eilish", "assets/songs/birdsofafeather.wav", "assets/covers/birdsofafeather.png", "assets/covers/birdsofafeather.png",
        {
            {0.0f, ""},
            {4.0f, "I want you to stay"},
            {8.0f, "'Til I'm in the grave"},
            {13.0f, "'Til I rot away, dead and buried"},
            {17.0f, "'Til I'm in the casket you carry"},
            {22.0f, "If you go, I'm going too, uh"},
            {26.5f, "'Cause it was always you, alright"},
            {31.0f, "And if I'm turnin' blue, please don't save me"},
            {36.0f, "Nothing left to lose without my baby"},
            {42.0f, "Birds of a feather, we"},
            {44.0f, "should stick together, I know"},
            {46.5f, "I said I'd never think I wasn't better alone"},
            {51.0f, "Can't change the weather,"},
            {53.0f, "might not be forever"},
            {55.0f, "But if it's forever, it's even better"},
            {60.0f, "And I don't know what I'm cryin' for"},
            {65.0f, "I don't think I could love you more"},
            {69.0f, "It might not be long, but baby, I"},
            {75.5f, "I'll love you 'til the day that I die"},
            {81.0f, "'Til the day that I die"},
            {86.0f, "'Til the light leaves my eyes"},
            {90.0f, "'Til the day that I die"},
            {95.0f, "I want you to see, hm"},
            {100.0f, "How you look to me, hm"},
            {104.5f, "You wouldn't believe if I told ya"},
            {109.0f, "You would keep the compliments I throw ya"},
            {113.0f, "But you're so full of shit, uh"},
            {118.0f, "Tell me it's a bit, no"},
            {123.0f, "Say you don't see it, your mind's polluted"},
            {127.5f, "Say you wanna quit, don't be stupid"},
            {133.5f, "And I don't know what I'm cryin' for"},
            {138.5f, "I don't think I could love you more"},
            {143.0f, "Might not be long, but baby, I"},
            {149.5f, "Don't wanna say goodbye"},
            {154.0f, "'til the day that I die"},
            {158.5f, "'til the light leaves my eyes"},
            {163.0f, "'til the day I die"},
            {170.0f, "I knew you in another life"},
            {175.0f, "You had that same look in your eyes"},
            {180.0f, "I love you, don't act so surprised"},
            {185.0f, ""}
        }
    },

    {"Cancer", "My Chemical Romance", "assets/songs/cancer.wav", "assets/covers/cancer.png", "assets/covers/cancer.png",
        {
            {13.0f, "Turn away"},
            {13.0f, "Turn away"},
            {17.1f, "If you could, get me a drink"},
            {21.0f, "Of water 'cause my lips are chapped"},
            {24.0f, "And faded, call my aunt marie"},
            {30.0f, "Help her gather all my things"},
            {33.8f, "And bury me in all my favorite colors"},
            {38.2f, "My sister and my brothers,"},
            {41.0f, "Still i will not kiss you"},
            {50.9f, "Cause the hardest part of this"},
            {55.0f, "Is leaving you"},
            {64.1f, "Now turn away"},
            {68.0f, "Cause i'm awful just to see"},
            {72.2f, "Cause all my hair's abandoned"},
            {75.2f, "All my body oh, my agony"},
            {81.0f, "Know that i will never marry"},
            {85.0f, "baby, i'm just soggy from the chemo"},
            {89.0f, "But counting down the days to go"},
            {94.0f, "It just ain't living"},
            {97.7f, "And i just hope you know"},
            {102.0f, "That if you say goodbye today"},
            {108.5f, "I'd ask you to be true"},
            {114.0f, "Cause the hardest part of this"},
            {119.5f, "is leaving you"},
            {127.0f, "Cause the hardest part of this"},
            {131.9f, "is leaving you"},
        } },

    {"Duvet", "Boa", "assets/songs/duvettt.wav", "assets/covers/duvet.png", "assets/covers/duvet.png",
        {
            { 1.0f, "And you don't seem to understand" },
            { 6.0f, "A shame you seemed an honest man" },
            { 11.0f, "And all the fears you hold so dear" },
            { 16.0f, "Will turn to whisper in your ear" },
            { 21.0f, "And you know what they say might hurt you" },
            { 24.0f, "And you know that it means so much" },
            { 27.0f, "And you don't even feel a thing" },
            { 31.0f, "I am falling, I am fading" },
            { 37.0f, "I have lost it all" },
            { 41.0f, "And you don't seem the lying kind" },
            { 47.0f, "A shame that I can read your mind" },
            { 52.0f, "And all the things that I read there" },
            { 57.0f, "Candlelit smile that we both share" },
            { 62.0f, "And you know I don't mean to hurt you" },
            { 65.0f, "But you know that it means so much" },
            { 68.0f, "And you don't even feel a thing" },
            { 73.0f, "I am falling, I am fading"},
            { 78.0f, "I am drowning" },
            { 80.0f, "Help me to breathe" },
            { 83.0f, "I am hurting, I have lost it all" },
            { 89.0f, "I am losing" },
            { 91.0f, "Help me to breathe" },
            { 96.0f, "..." },
            { 135.0f, "I am falling, I am failing"},
            { 140.0f, "I am drowning" },
            { 143.0f, "Help me to breathe" },
            { 145.0f, "I am hurting, I have lost it all" },
            { 150.0f, "I am losing" },
            { 153.0f, "Help me to breathe" },
            { 157.0f, "Oh-oh, yeah" },
            { 168.0f, "Oh-oh-oh-oh, yeah" },
            { 176.0f, "I am falling, I am failing"},
            { 181.0f, "I am drowning" },
            { 184.0f, "Help me to breathe" },
            { 186.0f, "I am hurting, I have lost it all" },
            { 192.0f, "I am losing" },
            { 194.0f, "Help me to breathe" },
        } },
    {"Blue", "Yungkai", "assets/songs/Blue.wav", "assets/covers/blue.png", "assets/covers/blue.png",
        {
            { 19.0f, "Your morning eyes" },
            { 21.5f, "I could stare like watching stars" },
            { 26.0f, "I could walk you by" },
            { 30.0f, "And I'll tell without a thought" },
            { 32.5f, "You'd be mine" },
            { 35.0f, "Would you mind" },
            { 37.0f, "If I took your hand tonight?" },
            { 40.0f, "Know you're all that I want this life" },

            { 48.5f, "I'll imagine we fell in love" },
            { 50.5f, "I'll nap under moonlight skies with you" },
            { 54.5f, "I think I'll picture us" },
            { 57.0f, "You with the waves" },
            { 58.5f, "The oceans colors on your face" },
            { 62.0f, "I'll leave my heart with your air" },
            { 66.5f, "So let me fly with you" },
            { 69.5f, "Will you be forever with me?" },
            { 73.0f, "..." },

            { 106.5f, "My love will always stay by you" },
            { 113.0f, "I'll keep it safe" },
            { 115.5f, "So don't you worry a thing" },
            { 118.0f, "I'll tell you I love you more" },
            { 121.5f, "It's stuck with you forever" },
            { 125.5f, "So promise you won't let it go" },
            { 128.5f, "I'll trust the universe" },
            { 130.0f, "Will always bring me to you" },

            { 136.6f, "I'll imagine we fell in love" },
            { 140.0f, "I'll nap under moonlight skies with you" },
            { 143.5f, "I think I'll picture us" },
            { 145.5f, "You with the waves" },
            { 146.0f, "The oceans colors on your face" },
            { 150.5f, "I'll leave my heart with your air" },
            { 155.0f, "So let me fly with you" },
            { 168.0f, "Will you be forever with me?" },
        }},
    {"Kissme", "Sixpence None The Richer", "assets/songs/kissme.wav", "assets/covers/kissme.png", "assets/covers/kissme.png",
        {
            {20.7f, "Kiss me, out of the bearded barley"},
            {25.5f, "Nightly, beside the green, green grass"},
            {30.0f, "Swing, swing, swing the spinning step"},
            {34.9f, "You wear those shoes"},
            {36.0f, "And i will wear that dress"},
            {38.7f, "Oh, kiss me, beneath the milky twilight"},
            {44.0f, "Lead me out on the moonlit floor"},
            {49.2f, "Lift your open hand"},
            {51.8f, "Strike up the band and make the fireflies"},
            {55.0f, "Dance silver moon's sparkling"},
            {60.0f, "So kiss me"},
            {71.0f, "Kiss me down by the broken tree house"},
            {76.0f, "Swing me upon its hanging tire"},
            {80.8f, "Bring, bring, bring your flowered hat"},
            {85.0f, "Well take the trail marked"},
            {86.8f, "On your father's map"},
            {88.7f, "Oh, kiss me, beneath the milky twilight"},
            {95.0f, "Lead me out on the moonlit floor"},
            {100.0f, "Lift your open hand"},
            {102.0f, "Strike up the band and make the fireflies"},
            {104.9f, "Dance silver moon's sparkling"},
            {110.2f, "So kiss me"},
            {113.2f, ""},
            {140.2f, "Kiss me, beneath the milky twilight"},
            {145.0f, "Lead me out on the moonlit floor"},
            {150.2f, "Lift your open hand"},
            {152.0f, "Strike up the band and make the fireflies"},
            {155.0f, "Dance silver moon's sparkling"},
            {161.0f, "So kiss me"},
            {170.7f, "So kiss me"},
            {180.0f, "So kiss me"},
            {189.8f, "So kiss me"},
        } },

    {"Linger", "The Cranberries", "assets/songs/linger.wav", "assets/covers/linger.png", "assets/covers/linger.png",
        {
            {50.0f, "If you, if you could return"},
            {54.0f, "Don't let it burn, don't let it fade"},
            {59.0f, "I'm sure, I'm not being rude"},
            {62.0f, "But it's just your attitude"},
            {64.0f, "It's tearing me apart"},
            {67.0f, "Is ruining everything"},
            {70.0f, "I swore, I swore I would be true"},
            {74.0f, "And honey, so did you"},
            {78.0f, "So why were you holding her hand?"},
            {82.0f, "Is that the way we stand?"},
            {84.0f, "Were you lying all the time?"},
            {86.0f, "Was it just a game to you?"},
            {90.0f, "But I'm in so deep"},
            {94.5f, "You know I'm such a fool for you"},
            {99.5f, "You got me wrapped around your finger"},
            {105.0f, "Do you have to let it linger?"},
            {107.0f, "Do you have to, do you have to"},
            {110.0f, "Do you have to let it linger?"},
            {114.1f, "Oh, I thought the world of you"},
            {120.5f, "I thought nothing could go wrong"},
            {125.8f, "But I was wrong, I was wrong"},
            {131.0f, "If you, if you could get by"},
            {135.0f, "Trying not to lie"},
            {139.7f, "Things wouldn't be so confused"},
            {143.0f, "And I wouldn't feel so used"},
            {145.7f, "But you always really knew"},
            {147.8f, "I just wanna be with you"},
            {151.0f, "And I'm in so deep"},
            {155.5f, "You know I'm such a fool for you"},
            {160.0f, "You got me wrapped around your finger"},
            {165.8f, "Do you have to let it linger?"},
            {168.8f, "Do you have to, do you have to"},
            {171.0f, "Do you have to let it linger?"},
            {175.0f, ""},
            {191.0f, "And I'm in so deep"},
            {195.0f, "You know I'm such a fool for you"},
            {200.9f, "You got me wrapped around your finger?"},
            {205.5f, "Do you have to let it linger?"},
            {209.0f, "Do you have to, do you have to"},
            {211.0f, "Do you have to let it linger?"},
            {215.9f, "You know I'm such a fool for you"},
            {221.0f, "You got me wrapped around your finger"},
            {226.7f, "Do you have to let it linger?"},
            {229.0f, "Do you have to, do you have to"},
            {232.0f, "Do you have to let it linger?"},
            {235.0f, ""},
        } },

    {"Shape Of You", "Ed Sheeran", "assets/songs/shapeofyou.wav", "assets/covers/shapeofyou.png", "assets/covers/shapeofyou.png",
        {
            {10.0f, "The club isn't the best place to find a lover"},
            {12.0f, "So the bar is where I go (mmmm)"},
            {15.0f, "Me and my friends at the table doing shots"},
            {17.0f, "Drinking fast and then we talk slow (mmmm)"},
            {20.0f, "And you come over"},
            {21.0f, "And start up a conversation with just me"},
            {22.0f, "And trust me I'll give it a chance now"},
            {24.0f, "Take my hand, stop, put Van The Man on the jukebox"},
            {26.0f, "put Van The Man on the jukebox"},
            {27.0f, "And then we start to dance"},
            {28.5f, "And now I'm singing like"},
            {30.0f, "Girl, you know I want your love"},
            {32.0f, "Your love was handmade"},
            {33.5f, "for somebody like me"},
            {35.5f, "Come on now, follow my lead"},
            {37.0f, "I may be crazy, don't mind me"},
            {39.5f, "Say, boy, let's not talk too much"},
            {42.0f, "Grab on my waist and put that body on me"},
            {45.0f, "Come on now, follow my lead"},
            {47.0f, "Come, come on now, follow my lead (mmmm)"},
            {50.0f, "I'm in love with the shape of you"},
            {53.0f, "We push and pull like a magnet do"},
            {55.0f, "Although my heart is falling too"},
            {58.0f, "I'm in love with your body"},
            {60.0f, "Last night you were in my room"},
            {63.0f, "And now my bedsheets smell like you"},
            {65.0f, "Every day discovering something brand new"},
            {68.0f, "I'm in love with your body"},
            {70.0f, "Oh I oh I oh I oh I"},
            {73.0f, "I'm in love with your body"},
            {75.0f, "Oh I oh I oh I oh I"},
            {78.0f, "I'm in love with your body"},
            {80.0f, "Oh I oh I oh I oh I"},
            {83.0f, "I'm in love with your body"},
            {85.0f, "Every day discovering something brand new"},
            {88.0f, "I'm in love with the shape of you"},
            {90.0f, "One week in we let the story begin"},
            {92.0f, "We're going out on our first date (mmmm)"},
            {94.0f, "You and me are thrifty, so go all you can eat"},
            {97.0f, "Fill up your bag and I fill up a plate (mmmm)"},
            {99.0f, "We talk for hours and hours"},
            {99.0f, "about the sweet and the sour"},
            {101.0f, "And how your family is doing okay (mmmm)"},
            {104.0f, "And leave and get in a taxi,"},
            {106.0f, "then kiss in the backseat"},
            {107.0f, "Tell the driver make the radio play"},
            {109.0f, "And I'm singing like"},
            {110.0f, "Girl, you know I want your love"},
            {112.0f, "Your love was handmade"},
            {114.0f, "for somebody like me"},
            {115.5f, "Come on now, follow my lead"},
            {117.0f, "I may be crazy, don't mind me"},
            {119.5f, "Say, boy, let's not talk too much"},
            {122.0f, "Grab on my waist and put that body on me"},
            {125.0f, "Come on now, follow my lead"},
            {127.0f, "Come, come on now, follow my lead (mmmm)"},
            {130.0f, "I'm in love with the shape of you"},
            {133.0f, "We push and pull like a magnet do"},
            {135.0f, "Although my heart is falling too"},
            {138.0f, "I'm in love with your body"},
            {140.0f, "Last night you were in my room"},
            {143.0f, "And now my bedsheets smell like you"},
            {145.0f, "Every day discovering something brand new"},
            {148.0f, "I'm in love with your body"},
            {150.0f, "Oh I oh I oh I oh I"},
            {153.0f, "I'm in love with your body"},
            {155.0f, "Oh I oh I oh I oh I"},
            {158.0f, "I'm in love with your body"},
            {160.0f, "Oh I oh I oh I oh I"},
            {163.0f, "I'm in love with your body"},
            {165.0f, "Every day discovering something brand new"},
            {168.0f, "I'm in love with the shape of you"},
            {170.0f, "Come on, be my baby, come on"},
            {172.0f, "Come on, be my baby, come on"},
            {175.0f, "Come on, be my baby, come on"},
            {177.0f, "Come on, be my baby, come on"},
            {179.5f, "Come on, be my baby, come on"},
            {182.0f, "Come on, be my baby, come on"},
            {185.0f, "Come on, be my baby, come on"},
            {187.0f, "Come on, be my baby, come on"},
            {190.0f, "I'm in love with the shape of you"},
            {193.0f, "We push and pull like a magnet do"},
            {195.0f, "Although my heart is falling too"},
            {198.0f, "I'm in love with your body"},
            {200.0f, "Last night you were in my room"},
            {203.0f, "And now my bedsheets smell like you"},
            {205.0f, "Every day discovering something brand new"},
            {208.0f, "I'm in love with your body"},
            {210.0f, "Come on, be my baby, come on"},
            {213.0f, "I'm in love with your body"},
            {215.0f, "Come on, be my baby, come on"},
            {217.5f, "I'm in love with your body"},
            {220.0f, "Come on, be my baby, come on"},
            {223.0f, "I'm in love with your body"},
            {225.0f, "Every day discovering something brand new"},
            {228.0f, "I'm in love with the shape of you"}
        } },

    {"Somewhere Only We Know", "Keane", "assets/songs/somewhereonlyweknow.wav", "assets/covers/somewhereonlyweknow.png", "assets/covers/somewhereonlyweknow.png",
        {
            {23.0f, "I walked across an empty land"},
            {29.0f, "I knew the pathway"},
            {31.0f, "like the back of my hand"},
            {34.8f, "I felt the earth beneath my feet"},
            {40.2f, "Sat by the river and it made me complete"},
            {45.8f, "Oh, simple thing, where have you gone?"},
            {50.5f, "I'm getting old"},
            {53.0f, "And I need something to rely on"},
            {57.0f, "So, tell me when you're gonna let me in"},
            {62.6f, "I'm getting tired"},
            {64.0f, "and I need somewhere to begin"},
            {67.0f, "I came across a fallen tree"},
            {74.0f, "I felt the branches of it looking at me"},
            {79.5f, "Is this the place we used to love?"},
            {84.5f, "Is this the place"},
            {86.0f, "That I've been dreaming of?"},
            {90.0f, "Oh, simple thing, where have you gone?"},
            {96.0f, "I'm getting old"},
            {97.5f, "And I need something to rely on"},
            {101.0f, "So, tell me when you're gonna let me in"},
            {106.5f, "I'm getting tired"},
            {109.0f, "And I need somewhere to begin"},
            {113.0f, "And if you have a minute, why don't we go"},
            {118.6f, "Talk about it somewhere only we know?"},
            {124.0f, "This could be the end of everything"},
            {129.0f, "So, why don't we go"},
            {131.5f, "Somewhere only we know?"},
            {136.8f, "Somewhere only we know"},
            {146.0f, "Oh, simple thing, where have you gone?"},
            {152.0f, "I'm getting old"},
            {153.5f, "And I need something to rely on"},
            {157.2f, "So, tell me when you're gonna let me in"},
            {162.7f, "I'm getting tired"},
            {165.0f, "And I need somewhere to begin"},
            {169.1f, "And if you have a minute, why don't we go"},
            {175.0f, "Talk about it somewhere only we know?"},
            {180.0f, "This could be the end of everything"},
            {184.8f, "So, why don't we go?"},
            {188.0f, "So, why don't we go?"},
            {192.0f, "Ooh, ah"},
            {198.0f, "So, why don't we go?"},
            {202.8f, "This could be the end of everything"},
            {207.2f, "So, why don't we go somewhere only we know?"},
            {209.2f, "somewhere only we know?"},
            {215.0f, "Somewhere only we know"},
            {221.0f, "Somewhere only we know"},
        } },
    { "Sparks", "Coldplay", "assets/songs/sparks.wav", "assets/covers/sparks.png", "assets/covers/sparks.png",
        {
            { 0.0f, "..." },
            { 32.0f, "Did I drive you away?" },
            { 38.0f, "I know what you'll say" },
            { 41.0f, "You say, 'Oh, sing one you know'" },
            { 54.0f, "But I promise you this" },
            { 59.0f, "I'll always look out for you" },
            { 66.0f, "Yeah, that's what I'll do" },
            { 73.0f, "I say oh" },
            { 83.0f, "I say oh" },
            { 116.0f, "My heart is yours" },
            { 121.0f, "It's you that I hold on to" },
            { 129.0f, "Yeah, that's what I do" },
            { 137.0f, "And I know I was wrong" },
            { 142.0f, "But I won't let you down" },
            { 147.0f, "Oh yeah, oh yeah, oh yeah, I will, yes I will" },
            { 156.0f, "I say oh" },
            { 166.0f, "I cry oh" },
            { 176.0f, "Yeah I saw sparks" },
            { 181.0f, "Yeah I saw sparks" },
            { 187.0f, "And I saw sparks" },
            { 192.0f, "Yeah I saw sparks" },
            { 198.0f, "Sing it out" },
            { 200.0f, "La, la, la, la, oh" },
            { 205.0f, "La, la, la, la, oh" },
            { 210.0f, "La, la, la, la, oh" },
            { 215.0f, "La, la, la, la, oh" },
            { 221.0f, "" },
        } },

    {"Take A Chance With Me", "NIKI", "assets/songs/takeachancewithme.wav", "assets/covers/takeachancewithme.png", "assets/covers/takeachancewithme.png",
        {
            { 16.5f, "His laugh you'd die for," },
            { 19.0f, "His laugh you'd die for," },
            { 21.0f, "the kind that colors the sky" },
            { 26.5f, "Heart intangible, slips away faster" },
            { 31.0f, "Than dandelion fluff in the sunlight" },
            { 36.0f, "And he's got swirls of passion in his eyes" },
            { 42.0f, "Uncovering the dreams he dreams at night" },
            { 46.5f, "As much and hard as he tries to hide" },
            { 50.0f, "I can see right through, see right through" },
            { 57.0f, "His voice you'd melt for," },
            { 60.0f, "he says my name like" },
            { 62.0f, "I'd fade away if he's too loud" },
            { 67.0f, "What I would give for me to get my feet" },
            { 72.5f, "Back on the ground, head off the clouds" },
            { 77.0f, "I laugh at how we're polar opposites" },
            { 82.0f, "I read him like a book, he's clueless" },
            { 84.0f, "he's clueless little kid" },
            { 87.0f, "Doesn't know that I'd stop time and space" },
            { 91.0f, "Just to make him smile, make him smile" },
            { 98.0f, "Oh, why can't we for once" },
            { 102.0f, "Say what we want, say what we feel?" },
            { 108.0f, "Oh, why can't you for once" },
            { 112.0f, "Disregard the world and run" },
            { 114.0f, "to what you know is real" },
            { 117.0f, "Take a chance with me, " },
            { 119.5f, "take a chance with me" },
            { 124.0f, "Ooh-ooh, ooh-ooh" },
            { 134.0f, "Ooh-ooh, ooh-ooh" },
            { 141.0f, "His kiss you'd kill for, " },
            { 144.0f, "just one and you're done for," },
            { 146.0f, "Electricity surging in the air" },
            { 152.0f, "He drives me crazy, it's so beyond me" },
            { 156.0f, "How he'd look me dead in the eye" },
            { 158.0f, "Stay unaware" },
            { 161.0f, "That I'm hopelessly captivated" },
            { 166.0f, "By a boy who thinks love's overrated" },
            { 171.0f, "How did I get myself in this arrangement" },
            { 175.0f, "It baffles me too, baffles me too" },
            { 182.0f, "Oh, why can't we for once" },
            { 186.0f, "Say what we want, say what we feel?" },
            { 192.0f, "Oh, why can't you for once" },
            { 196.0f, "Disregard the world and run" },
            { 198.0f, "To what you know is real" },
            { 202.0f, "In the end, we only regret" },
            { 207.0f, "The chances we didn't take" },
            { 213.0f, "I'll be your safety net" },
            { 217.0f, "So why not raise the stakes?" },
            { 222.0f, "And I can hear your heart" },
            { 224.5f, "from across the room" },
            { 227.0f, "Pulsin' through my veins,"},
            { 229.0f, "I know you need this too" },
            { 233.0f, "Lie to me all you please" },
            { 236.0f, "I can see right through, see right through" },
            { 243.0f, "Oh, why can't we for once" },
            { 247.0f, "Say what we want, say what we feel?" },
            { 253.0f, "Oh, why can't you for once" },
            { 257.0f, "Disregard the world and run," },
            { 260.0f, "To what you know is real" },
            { 263.0f, "Oh, why can't we for once" },
            { 267.0f, "Say what we want, say what we feel?" },
            { 274.0f, "Oh, why can't you for once" },
            { 278.0f, "Disregard the world and run," },
            { 280.0f, "To what you know is real" },
            { 281.5f, "Take a chance with me," },
            { 285.0f, "Take a chance with me" },
            { 290.0f, "Ooh-ah, oh-oh, oh" },
            { 295.0f, "" }
        } },

    {"The Man Who Can't Be", "The Script", "assets/songs/themanwhocantbemoved.wav", "assets/covers/themanwhocantbemoved.png", "assets/covers/themanwhocantbemoved.png",
            {{9.0f, "Going back to the corner"},
            {11.5f, "where I first saw you"},
            {14.0f, "Gonna camp in my sleeping bag"},
            {16.0f, "I'm not gonna move"},
            {19.0f, "Got some words on cardboard"},
            {21.0f, "Got your picture in my hand"},
            {23.5f, "Saying, 'If you see this girl'"},
            {26.0f, "Can you tell her where I am?"},
            {28.0f, "Some try to hand me money"},
            {30.5f, "They don't understand"},
            {33.0f, "I'm not broke"},
            {36.0f, "I'm just a broken hearted man"},
            {38.0f, "I know it makes no sense"},
            {40.0f, "But what else can I do"},
            {43.0f, "How can I move on"},
            {45.0f, "When I'm still in love with you"},
            {47.0f, "Cause if one day you wake up"},
            {50.0f, "And find that you're missing me"},
            {53.0f, "And your heart starts to wonder "},
            {55.2f, "Where on this Earth I could be"},
            {56.5f, "Thinkin' maybe you'll come back"},
            {58.5f, "Here to the place that we'd meet"},
            {62.0f, "And you'll see me waiting for you"},
            {64.5f, "On the corner of the street"},
            {66.0f, "So I'm not moving, I'm not moving"},
            {87.5f, "Policeman says, 'Son, you can't stay here'"},
            {91.0f, "I said, 'There's someone I'm waiting for'"},
            {93.0f, "If it's a day, a month, a year"},
            {95.0f, "Gotta stand my ground"},
            {98.5f, "Even if it rains or snows"},
            {100.5f, "If she changes her mind"},
            {102.0f, "This is the first place she will go"},
            {105.0f, "Cause if one day you wake up"},
            {106.5f, "And find that you're missing me"},
            {110.0f, "And your heart starts to wonder"},
            {112.0f, "Where on this Earth I could be"},
            {114.0f, "Thinking maybe you'll come back"},
            {116.5f, "Here to the place that we'd meet"},
            {119.0f, "And you'll see me waiting for you"},
            {121.5f, "On the corner of the street"},
            {124.0f, "So I'm not moving, I'm not moving"},
            {133.0f, "I'm not moving, I'm not moving"},
            {144.5f, "People talk about the guy"},
            {147.0f, "That's waiting on a girl (woah)"},
            {154.0f, "There are no holes in his shoes"},
            {157.0f, "But a big hole in his world"},
            {162.0f, "Maybe I'll get famous"},
            {164.5f, "As the man who can't be moved"},
            {168.0f, "Maybe you won't mean to"},
            {169.5f, "But you'll see me on the news"},
            {171.5f, "And you'll come running to the corner"},
            {175.0f, "'Cause you'll know it's just for you"},
            {178.5f, "I'm the man who can't be moved"},
            {184.0f, "I'm the man who can't be moved"},
            {186.0f, "'Cause if one day you wake up"},
            {189.0f, "And find that you're missing me"},
            {189.0f, "(Find that you're missing me)"},
            {191.5f, "And your heart starts to wonder"},
            {193.5f, "Where on this Earth I could be "},
            {193.5f, "(Where on this Earth I could be)"},
            {196.0f, "Thinkin' maybe you'll come back"},
            {198.0f, "Here to the place that we'd meet"},
            {198.0f, "(To the place that we'd meet)"},
            {200.5f, "And you'll see me waiting for you"},
            {203.5f, "On the corner of the street"},
            {205.5f, "'Cause if one day you wake up"},
            {207.0f, "And find that you're missing me"},
            {210.0f, "And your heart starts to wonder"},
            {213.0f, "Where on this Earth I could be"},
            {216.0f, "Thinkin' maybe you'll come back"},
            {218.5f, "Here to the place that we'd meet"},
            {220.5f, "And you'll see me waiting for you"},
            {223.5f, "On the corner of the street"},
            {225.5f, "Going back to the corner"},
            {227.5f, "Where I first saw you"},
            {230.0f, "Gonna camp in my sleeping bag"},
            {233.0f, "I'm not gonna move"}
        }
    },

    {"The Night We Met", "Lord Huron", "assets/songs/thenightwemet.wav", "assets/covers/thenightwemet.png", "assets/covers/thenightwemet.png",
        {
            {0.0f, ""},
            {1.5f, "Ooo...."},
            {15.0f, "Ooo...."},
            {30.0f, "I am not the only traveler"},
            {37.0f, "Who has not repaid his debt"},
            {44.0f, "I've been searching for a trail to follow again"},
            {51.0f, "Take me back to the night we met"},
            {58.5f, "And then I can tell myself"},
            {65.5f, "What the hell I'm supposed to do"},
            {73.0f, "And then I can tell myself"},
            {80.5f, "Not to ride along with you"},
            {87.5f, "I had all and then most of you"},
            {90.0f, "Some and now none of you"},
            {94.5f, "Take me back to the night we met"},
            {102.0f, "I don't know what I'm supposed to do"},
            {105.0f, "Haunted by the ghost of you"},
            {109.0f, "Oh, take me back to the night we met"},
            {116.0f, "When the night was full of terrors"},
            {123.0f, "And your eyes were filled with tears"},
            {131.0f, "When you had not touched me yet"},
            {138.0f, "Oh, take me back to the night we met"},
            {145.0f, "I had all and then most of you"},
            {148.5f, "Some and now none of you"},
            {153.0f, "Take me back to the night we met"},
            {160.0f, "I don't know what I'm supposed to do"},
            {162.5f, "Haunted by the ghost of you"},
            {167.0f, "Take me back to the night we met"},
            {172.0f, ""},
        } },
    { "Uptown Funk", "Mark Ronson ft. Bruno Mars", "assets/songs/uptownfunk.wav", "assets/covers/uptownfunk.png", "assets/covers/uptownfunk.png",
        {
            { 0.0f, "Doh" },
            { 0.5f, "Doh-doh-doh, doh-doh-doh, doh-doh" },
            { 5.5f, "Doh-doh-doh, doh-doh-doh, doh-doh" },
            { 10.5f, "Doh-doh-doh, doh-doh-doh, doh-doh" },
            { 14.5f, "Doh-doh-doh, doh-doh, (ah, ow)" },
            { 16.0f, "This hit, that ice cold," },
            { 19.0f, "Michelle Pfeiffer, that white gold" },
            { 21.0f, "This one, for them hood girls," },
            { 23.0f, "Them good girls, straight masterpieces." },
            { 25.0f, "Stylin', wilin', livin' it up in the city," },
            { 29.0f, "Got Chucks on with Saint Laurent." },
            { 31.0f, "Gotta kiss myself, I'm so pretty." },

            { 33.0f, "I'm too hot (Hot damn)," },
            { 35.0f, "Call the police and the fireman." },
            { 37.0f, "I'm too hot (Hot damn)," },
            { 39.0f, "Make a dragon wanna retire, man." },
            { 41.0f, "I'm too hot (Hot damn)," },
            { 44.0f, "Say my name, you know who I am." },
            { 46.0f, "I'm too hot (Hot damn)," },
            { 47.0f, "N my band 'bout that money, break it down." },

            { 50.0f, "Girls hit your hallelujah (Woo!)," },
            { 52.0f, "Girls hit your hallelujah (Woo!)," },
            { 54.0f, "Girls hit your hallelujah (Woo!)," },
            { 56.0f, "'Cause Uptown Funk gon' give it to you." },
            { 58.0f, "'Cause Uptown Funk gon' give it to you." },
            { 60.0f, "'Cause Uptown Funk gon' give it to you." },
            { 62.0f, "Saturday night and we in the spot." },
            { 64.0f, "Don't believe me, just watch." },
            { 67.0f, "Doh" },
            { 68.5f, "Doh-doh-doh, doh-doh-doh, doh-doh(ya)" },
            { 73.0f, "Don't believe me, just watch." },
            { 75.5f, "Doh" },
            { 77.0f, "Doh-doh-doh, doh-doh-doh, doh-doh(ya)" },
            { 81.0f, "Don't believe me, just watch." },
            { 83.0f, "Don't believe me, just watch." },
            { 85.0f, "Don't believe me, just watch." },
            { 87.0f, "Don't believe me, just watch." },
            { 89.0f, "Hey, hey, hey, oh." },
            { 92.0f, "Stop, wait a minute!" },
            { 94.0f, "Fill my cup, put some liquor in it." },
            { 96.0f, "Take a sip, sign the check." },
            { 98.0f, "Julio! Get the stretch!" },
            { 100.0f, "Ride to Harlem," },
            { 101.5f, "Hollywood, Jackson, Mississippi." },
            { 104.0f, "If we show up, we gon' show out." },
            { 106.0f, "Smoother than a fresh jar of Skippy." },

            { 108.0f, "I'm too hot (Hot damn)," },
            { 110.0f, "Call the police and the fireman." },
            { 112.0f, "I'm too hot (Hot damn)," },
            { 114.0f, "Make a dragon wanna retire, man." },
            { 117.0f, "I'm too hot (Hot damn)," },
            { 119.0f, "Bitch, say my name you know who I am." },
            { 121.0f,"I'm too hot (Hot damn)," },
            { 123.0f,"And my band 'bout that money, break it down." },

            { 125.0f,"Girls hit your hallelujah (Woo!)," },
            { 127.0f,"Girls hit your hallelujah (Woo!)," },
            { 129.0f,"Girls hit your hallelujah (Woo!)," },
            { 131.0f,"'Cause Uptown Funk gon' give it to you." },
            { 133.0f,"'Cause Uptown Funk gon' give it to you." },
            { 135.0f,"'Cause Uptown Funk gon' give it to you." },
            { 137.0f,"Saturday night and we in the spot." },
            { 139.0f,"Don't believe me, just watch, come on" },

            { 142.0f,"Doh-doh-doh, doh-doh-doh, doh-doh." },
            { 148.0f,"Don't believe me, just watch." },
            { 150.0f,"Doh-doh-doh, doh-doh-doh, doh-doh." },
            { 156.0f,"Don't believe me, just watch." },
            { 158.0f,"Don't believe me, just watch." },
            { 160.0f,"Don't believe me, just watch." },
            { 162.0f,"Don't believe me, just watch." },
            { 164.0f,"Hey, hey, hey, oh!" },
            { 167.0f, "Doh - doh - doh, doh - doh - doh, doh - doh." },
            { 173.0f, "Let me tell y'all a lil' something" },
            { 175.0f, "Uptown funk you up, uptown funk you up" },
            { 179.0f, "Uptown funk you up, uptown funk you up" },
            { 183.0f, "I said, uptown funk you up, " },
            { 185.0f, "uptown funk you up" },
            { 187.0f, "Uptown funk you up, uptown funk you up" },
            { 192.0f, "come on, Dance, jump on it" },
            { 194.0f, "If you sexy, then flaunt it" },
            { 196.0f, "If you freaky, then own it" },
            { 198.0f, "Don't brag about it, come show me" },
            { 200.0f, "Come on, Dance, jump on it" },
            { 202.0f, "If you sexy, then flaunt it" },
            { 204.0f, "Well, it's Saturday night and we in the spot" },
            { 206.0f, "Don't believe me, just watch, come on" },

            { 209.0f,"Doh-doh-doh, doh-doh-doh, doh-doh." },
            { 215.0f,"Don't believe me, just watch." },
            { 217.0f,"Doh-doh-doh, doh-doh-doh, doh-doh." },
            { 223.0f,"Don't believe me, just watch." },
            { 225.0f,"Don't believe me, just watch." },
            { 228.0f,"Don't believe me, just watch." },
            { 230.0f,"Don't believe me, just watch." },
            { 231.5f,"Hey, hey, hey, oh!" },

            { 234.0f,"Uptown funk you up"},
            { 236.0f,"Uptown funk you up"},
            { 238.0f,"Uptown funk you up"},
            { 240.0f,"Uptown funk you up"},
            { 242.0f,"Uptown funk you up"},
            { 244.0f,"Uptown funk you up"},
            { 246.0f,"Uptown funk you up"},
            { 248.0f,"Uptown funk you up"},
            { 250.0f,"Uptown funk you up"},
            { 252.0f,"Uptown funk you up"},
            { 254.0f,"Uptown funk you up"},
            { 256.0f,"Uptown funk you up"},
            { 258.0f,"Uptown funk you up"},
            { 260.0f,"Uptown funk you up"},
            { 262.0f,"Uptown funk you up"},
            { 265.0f,"Ah, ow"},
        } }
};

// --- Variabel Global ---
int currentSongIndex = -1;
AppState appState = AppState::Home;
HomeSubState homeSubState = HomeSubState::BrowseSongs;

Font font;
Music music;
Texture coverTexture;
Sprite coverSprite;
vector<int> recommendedIndices;
int lyricsOffset = 0;
vector<Texture> thumbnails;
vector<Sprite> thumbnailSprites;
vector<int> songQueue;

bool isPlaying = false;
bool isRepeating = false;
float volume = 75.f;

Texture playTexture, pauseTexture, prevTexture, nextTexture, repeatOnTexture, repeatOffTexture;
Sprite playSprite, pauseSprite, prevSprite, nextSprite, repeatSprite;

int scrollOffset = 0;
const int visibleSongs = 5;
bool isDraggingScrollbar = false;

vector<int> historyIndices;
const int MAX_HISTORY_SIZE = 20;
const string HISTORY_FILE = "history.txt";

vector<Playlist> playlists;
const string PLAYLIST_FILE = "playlists.txt";
bool isCreatingNewPlaylist = false; 
string newPlaylistName = "";
int currentPlaylistViewIndex = -1;

bool showPlaylistSelectionPopup = false;
int songIndexForPlaylistAdd = -1; 


// Deklarasi fungsi 
void loadSong(int index);
void saveHistory();
void loadHistory();
void savePlaylists();
void loadPlaylists();
void addSongToSpecificPlaylist(int playlistIndex, int songIndex); 
void removeSongFromPlaylist(int playlistIndex, int songIndexToRemove); 
void deletePlaylist(int playlistIndex); 


// --- Fungsi untuk Memuat Semua Thumbnail di Awal ---
void loadAllThumbnails() {
    thumbnails.clear();
    thumbnailSprites.clear();
    thumbnails.resize(library.size());
    thumbnailSprites.resize(library.size());

    for (int i = 0; i < library.size(); ++i) {
        string thumbnailPath = library[i].thumbnailFile;
        string songTitle = library[i].title;

        if (!thumbnails[i].loadFromFile(thumbnailPath)) {
            cerr << "❌ Gagal memuat thumbnail untuk: " << songTitle << " (Path: " << thumbnailPath << ")" << endl;
            Image img;
            img.create(50, 50, Color(255, 105, 180)); 
            if (!thumbnails[i].loadFromImage(img)) {
                cerr << "Gagal memuat placeholder image untuk thumbnail!" << endl;
            }
        }

        thumbnailSprites[i].setTexture(thumbnails[i]);
        thumbnailSprites[i].setScale(
            50.f / thumbnails[i].getSize().x,
            50.f / thumbnails[i].getSize().y
        );
    }
    cout << "Selesai memuat semua thumbnail." << endl;
}

// --- Fungsi untuk Memilih Lagu Secara Acak (untuk daftar rekomendasi) ---
void pickRandomSongs() {
    vector<int> allIndices(library.size());
    iota(allIndices.begin(), allIndices.end(), 0);
    shuffle(allIndices.begin(), allIndices.end(), mt19937(random_device{}()));
    recommendedIndices = allIndices;
    scrollOffset = 0;
}

// --- Fungsi Histori ---
void addSongToHistory(int index) {
    if (!historyIndices.empty() && historyIndices[0] == index) {
        return;
    }
    historyIndices.insert(historyIndices.begin(), index);
    if (historyIndices.size() > MAX_HISTORY_SIZE) {
        historyIndices.pop_back();
    }
}

void saveHistory() {
    ofstream outFile(HISTORY_FILE);
    if (outFile.is_open()) {
        for (int index : historyIndices) {
            outFile << index << endl;
        }
        outFile.close();
        cout << "Histori berhasil disimpan ke " << HISTORY_FILE << endl;
    }
    else {
        cerr << "Gagal menyimpan histori ke " << HISTORY_FILE << endl;
    }
}

void loadHistory() {
    ifstream inFile(HISTORY_FILE);
    if (inFile.is_open()) {
        int index;
        while (inFile >> index) {
            if (index >= 0 && index < library.size()) {
                historyIndices.push_back(index);
            }
        }
        inFile.close();
        reverse(historyIndices.begin(), historyIndices.end());
        while (historyIndices.size() > MAX_HISTORY_SIZE) {
            historyIndices.pop_back();
        }
        cout << "Histori berhasil dimuat dari " << HISTORY_FILE << endl;
    }
    else {
        cerr << "Tidak dapat memuat histori dari " << HISTORY_FILE << ". File mungkin belum ada atau ada masalah." << endl;
    }
}

// --- Fungsi untuk Mengelola Queue ---
void addSongToQueue(int index) {
    songQueue.push_back(index);
    cout << "Ditambahkan ke antrian: " << library[index].title << endl;
}

void playNextFromQueue() {
    if (!songQueue.empty()) {
        int nextSongIdx = songQueue.front();
        songQueue.erase(songQueue.begin());
        loadSong(nextSongIdx);
    }
    else {
        currentSongIndex = (currentSongIndex + 1) % library.size();
        loadSong(currentSongIndex);
    }
    isPlaying = true;
}

void clearQueue() {
    songQueue.clear();
    cout << "Antrian telah dibersihkan." << endl;
}

// --- Fungsi Playlist ---
void savePlaylists() {
    ofstream outFile(PLAYLIST_FILE);
    if (outFile.is_open()) {
        outFile << playlists.size() << endl;
        for (const auto& pl : playlists) {
            outFile << pl.name << endl;
            outFile << pl.songIndices.size() << endl;
            for (int songIdx : pl.songIndices) {
                outFile << songIdx << endl;
            }
        }
        outFile.close();
        cout << "Playlist berhasil disimpan ke " << PLAYLIST_FILE << endl;
    }
    else {
        cerr << "Gagal menyimpan playlist ke " << PLAYLIST_FILE << endl;
    }
}

void loadPlaylists() {
    ifstream inFile(PLAYLIST_FILE);
    if (inFile.is_open()) {
        playlists.clear();
        int numPlaylists;
        inFile >> numPlaylists;
        inFile.ignore();

        for (int i = 0; i < numPlaylists; ++i) {
            Playlist newPlaylist;
            getline(inFile, newPlaylist.name);
            int numSongs;
            inFile >> numSongs;
            inFile.ignore();

            for (int j = 0; j < numSongs; ++j) {
                int songIdx;
                inFile >> songIdx;
                inFile.ignore();
                if (songIdx >= 0 && songIdx < library.size()) {
                    newPlaylist.songIndices.push_back(songIdx);
                }
            }
            playlists.push_back(newPlaylist);
        }
        inFile.close();
        cout << "Playlist berhasil dimuat dari " << PLAYLIST_FILE << endl;
    }
    else {
        cerr << "Tidak dapat memuat playlist dari " << PLAYLIST_FILE << ". File mungkin belum ada atau ada masalah." << endl;
    }
}

void addSongToSpecificPlaylist(int playlistIndex, int songIndex) {
    if (playlistIndex >= 0 && playlistIndex < playlists.size() &&
        songIndex >= 0 && songIndex < library.size()) {
        bool alreadyExists = false;
        for (int existingSongIdx : playlists[playlistIndex].songIndices) {
            if (existingSongIdx == songIndex) {
                alreadyExists = true;
                break;
            }
        }

        if (!alreadyExists) {
            playlists[playlistIndex].songIndices.push_back(songIndex);
            savePlaylists();
            cout << "Ditambahkan " << library[songIndex].title << " ke playlist '" << playlists[playlistIndex].name << "'" << endl;
        }
        else {
            cout << "'" << library[songIndex].title << "' sudah ada di playlist '" << playlists[playlistIndex].name << "'" << endl;
        }
    }
}

void removeSongFromPlaylist(int playlistIndex, int songIndexToRemove) {
    if (playlistIndex >= 0 && playlistIndex < playlists.size()) {
        auto& songs = playlists[playlistIndex].songIndices;
        auto it = remove(songs.begin(), songs.end(), songIndexToRemove); 
        if (it != songs.end()) { 
            songs.erase(it, songs.end());
            savePlaylists();
            cout << "Dihapus lagu dari playlist '" << playlists[playlistIndex].name << "'" << endl;
        }
        else {
            cout << "Lagu tidak ditemukan di playlist untuk dihapus." << endl;
        }
    }
}

void deletePlaylist(int playlistIndex) {
    if (playlistIndex >= 0 && playlistIndex < playlists.size()) {
        cout << "Menghapus playlist: " << playlists[playlistIndex].name << endl;
        playlists.erase(playlists.begin() + playlistIndex);
        savePlaylists();
        currentPlaylistViewIndex = -1; 
        homeSubState = HomeSubState::ViewPlaylists; 
        scrollOffset = 0;
    }
}


// --- Fungsi untuk Memuat dan Memutar Lagu ---
void loadSong(int index) {
    if (index < 0 || index >= library.size()) {
        cerr << "Invalid song index: " << index << endl;
        currentSongIndex = -1;
        return;
    }

    currentSongIndex = index;

    music.stop();
    if (!music.openFromFile(library[index].audioFile)) {
        cerr << "Failed to load audio: " << library[index].audioFile << endl;
        currentSongIndex = -1;
        isPlaying = false;
        return;
    }
    music.setVolume(volume);
    music.setLoop(isRepeating);
    music.play();
    isPlaying = true;

    addSongToHistory(index);

    if (coverTexture.loadFromFile(library[index].coverFile)) {
        cout << "Cover loaded successfully from file: " << library[index].coverFile << endl;
    }
    else {
        cerr << "Gagal load cover: " << library[index].coverFile << endl;
        RenderTexture rt_placeholder;
        rt_placeholder.create(300, 300);
        rt_placeholder.clear(Color(30, 30, 30));

        Text text(library[index].title, font, 24);
        text.setFillColor(Color(255, 105, 180));
        FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(rt_placeholder.getSize().x / 2.0f, rt_placeholder.getSize().y / 2.0f);

        rt_placeholder.draw(text);
        rt_placeholder.display();
        coverTexture = rt_placeholder.getTexture();
        cout << "Using placeholder cover for: " << library[index].title << endl;
    }

    coverSprite.setTexture(coverTexture);
    float scaleX = 300.f / coverTexture.getSize().x;
    float scaleY = 300.f / coverTexture.getSize().y;
    float finalScale = min(scaleX, scaleY);

    coverSprite.setScale(finalScale, finalScale);
    coverSprite.setOrigin(coverTexture.getSize().x / 2.0f, coverTexture.getSize().y / 2.0f);
    coverSprite.setPosition(50 + (300 / 2.0f), 100 + (300 / 2.0f));

    lyricsOffset = 0;
}

// --- Fungsi Utama (main) ---
int main() {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        cerr << "Error loading font! Make sure 'assets/fonts/arial.ttf' exists." << endl;
        return -1;
    }

    if (!playTexture.loadFromFile("assets/icons/play_icon.png")) {
        cerr << "Error loading play_icon.png! Make sure 'assets/icons/play_icon.png' exists." << endl;
        return -1;
    }
    if (!pauseTexture.loadFromFile("assets/icons/pause_icon.png")) {
        cerr << "Error loading pause_icon.png! Make sure 'assets/icons/pause_icon.png' exists." << endl;
        return -1;
    }
    if (!prevTexture.loadFromFile("assets/icons/prev_icon.png")) {
        cerr << "Error loading prev_icon.png! Make sure 'assets/icons/prev_icon.png' exists." << endl;
        return -1;
    }
    if (!nextTexture.loadFromFile("assets/icons/next_icon.png")) {
        cerr << "Error loading next_icon.png! Make sure 'assets/icons/next_icon.png' exists." << endl;
        return -1;
    }
    if (!repeatOnTexture.loadFromFile("assets/icons/repeat_on_icon.png")) {
        cerr << "Error loading repeat_on_icon.png! Make sure 'assets/icons/repeat_on_icon.png' exists." << endl;
        return -1;
    }
    if (!repeatOffTexture.loadFromFile("assets/icons/repeat_off_icon.png")) {
        cerr << "Error loading repeat_off_icon.png! Make sure 'assets/icons/repeat_off_icon.png' exists." << endl;
        return -1;
    }

    RenderWindow window(VideoMode(800, 600), "Audio Player", Style::Close);
    window.setFramerateLimit(60);

    loadAllThumbnails();
    pickRandomSongs();
    loadHistory();
    loadPlaylists(); 

    if (currentSongIndex == -1 && !library.empty()) {
        loadSong(0);
        music.stop();
        isPlaying = false;
    }

    string searchQuery;
    vector<int> filteredIndices;
    bool isSearching = false;

    float controlBtnScale = 0.09f;
    prevSprite.setTexture(prevTexture);
    prevSprite.setScale(controlBtnScale, controlBtnScale);
    prevSprite.setPosition(260, 500);

    nextSprite.setTexture(nextTexture);
    nextSprite.setScale(controlBtnScale, controlBtnScale);
    nextSprite.setPosition(460, 500);

    playSprite.setTexture(playTexture);
    playSprite.setScale(controlBtnScale, controlBtnScale);
    playSprite.setPosition(360, 500);

    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setScale(controlBtnScale, controlBtnScale);
    pauseSprite.setPosition(360, 500);

    repeatSprite.setScale(controlBtnScale, controlBtnScale);
    repeatSprite.setPosition(560, 500);

    // --- Loop Utama Aplikasi ---
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                saveHistory();
                savePlaylists(); 
                window.close();
            }
            else if (event.type == Event::TextEntered) {
                if (appState == AppState::Home) {
                    if (homeSubState == HomeSubState::BrowseSongs) {
                        if (event.text.unicode == '\b' && !searchQuery.empty()) {
                            searchQuery.pop_back();
                        }
                        else if (event.text.unicode == 27) { 
                            searchQuery.clear();
                            isSearching = false;
                        }
                        else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                            searchQuery += static_cast<char>(event.text.unicode);
                        }

                        isSearching = !searchQuery.empty();
                        filteredIndices.clear();
                        if (isSearching) {
                            string queryLower = searchQuery;
                            transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

                            for (int i = 0; i < library.size(); ++i) {
                                string titleLower = library[i].title;
                                string artistLower = library[i].artist;
                                transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);
                                transform(artistLower.begin(), artistLower.end(), artistLower.begin(), ::tolower);

                                if (titleLower.find(queryLower) != string::npos ||
                                    artistLower.find(queryLower) != string::npos) {
                                    filteredIndices.push_back(i);
                                }
                            }
                        }
                        scrollOffset = 0;
                    }
                    else if (homeSubState == HomeSubState::CreateNewPlaylist) {
                        if (event.text.unicode == '\b' && !newPlaylistName.empty()) {
                            newPlaylistName.pop_back();
                        }
                        else if (event.text.unicode == 13) { 
                            if (!newPlaylistName.empty()) { 
                                Playlist newPl;
                                newPl.name = newPlaylistName;
                                playlists.push_back(newPl);
                                savePlaylists(); 
                                newPlaylistName = ""; 
                                homeSubState = HomeSubState::ViewPlaylists; 
                                scrollOffset = 0;
                                cout << "Playlist baru dibuat: " << newPl.name << endl;
                            }
                            else {
                                cout << "Nama playlist tidak boleh kosong!" << endl;
                            }
                        }
                        else if (event.text.unicode == 27) { 
                            newPlaylistName = ""; 
                            homeSubState = HomeSubState::ViewPlaylists; 
                        }
                        else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                            newPlaylistName += static_cast<char>(event.text.unicode);
                        }
                    }
                }
            }
            
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (showPlaylistSelectionPopup) {
                    sf::FloatRect popupBgRect(200, 150, 400, 300);
                    if (popupBgRect.contains(mouse)) { 
                        sf::FloatRect cancelBtnRect(350, 410, 100, 30);
                        if (cancelBtnRect.contains(mouse)) {
                            showPlaylistSelectionPopup = false;
                            songIndexForPlaylistAdd = -1;
                            cout << "Pembatalan penambahan lagu ke playlist." << endl;
                            break; 
                        }
                        else {
                            int numPlaylistsInPopup = min((int)playlists.size(), 4);
                            for (int i = 0; i < numPlaylistsInPopup; ++i) {
                                sf::FloatRect plEntryRect(210, 180 + i * 50, 380, 40);
                                if (plEntryRect.contains(mouse)) {
                                    addSongToSpecificPlaylist(i, songIndexForPlaylistAdd);
                                    showPlaylistSelectionPopup = false;
                                    songIndexForPlaylistAdd = -1;
                                    break; 
                                }
                            }
                            break; 
                        }
                    }
                    else {
                        
                        showPlaylistSelectionPopup = false;
                        songIndexForPlaylistAdd = -1;
                        cout << "Klik di luar pop-up, menyembunyikan." << endl;
                        break; 
                    }
                }

                else if (appState == AppState::Home) {
                    sf::FloatRect backToPlayerButtonRect(670, 550, 80, 30);
                    if (currentSongIndex != -1 && backToPlayerButtonRect.contains(mouse)) {
                        appState = AppState::Player;                       
                        homeSubState = HomeSubState::BrowseSongs;
                        break; 
                    }

                    sf::FloatRect playlistButtonRect(510, 550, 150, 30); 
                    sf::FloatRect queueButtonRect(350, 550, 150, 30);  
                    sf::FloatRect historyButtonRect(190, 550, 150, 30); 
                    sf::FloatRect browseButtonRect(30, 550, 150, 30);  

                    if (playlistButtonRect.contains(mouse)) {
                        homeSubState = HomeSubState::ViewPlaylists;
                        searchQuery.clear(); isSearching = false; scrollOffset = 0;
                        break;
                    }
                    else if (queueButtonRect.contains(mouse)) {
                        homeSubState = HomeSubState::ViewQueue;
                        searchQuery.clear(); isSearching = false; scrollOffset = 0;
                        break;
                    }
                    else if (historyButtonRect.contains(mouse)) {
                        homeSubState = HomeSubState::ViewHistory;
                        searchQuery.clear(); isSearching = false; scrollOffset = 0;
                        break;
                    }
                    else if (browseButtonRect.contains(mouse)) {
                        homeSubState = HomeSubState::BrowseSongs;
                        searchQuery.clear(); isSearching = false; scrollOffset = 0;
                        break;
                    }

                    if (homeSubState == HomeSubState::BrowseSongs) {
                        const auto& displayList = isSearching ? filteredIndices : recommendedIndices;
                        int startIdx = scrollOffset;
                        int endIdx = min(startIdx + visibleSongs, (int)displayList.size());

                        for (int i = startIdx; i < endIdx; ++i) {
                            int displayPos = i - startIdx;
                            if (displayList[i] >= 0 && displayList[i] < library.size()) {
                                sf::FloatRect songArea(50, 100 + displayPos * 80, 620, 70); 

                                sf::RectangleShape addToQueueBtn(sf::Vector2f(40, 20));
                                addToQueueBtn.setPosition(610, 115 + displayPos * 80);
                                sf::FloatRect addToQueueButtonRect = addToQueueBtn.getGlobalBounds();

                                sf::RectangleShape addToPlaylistBtn(sf::Vector2f(40, 20));
                                addToPlaylistBtn.setPosition(655, 115 + displayPos * 80);
                                sf::FloatRect addToPlaylistButtonRect = addToPlaylistBtn.getGlobalBounds();

                                if (addToPlaylistButtonRect.contains(mouse)) {
                                    if (playlists.empty()) {
                                        cout << "Tidak ada playlist. Buat playlist baru terlebih dahulu." << endl;
                                        homeSubState = HomeSubState::CreateNewPlaylist;
                                        newPlaylistName = "";
                                    }
                                    else {
                                        songIndexForPlaylistAdd = displayList[i];
                                        showPlaylistSelectionPopup = true;
                                    }
                                    break;
                                }
                                else if (addToQueueButtonRect.contains(mouse)) {
                                    addSongToQueue(displayList[i]);
                                    break;
                                }
                                else if (songArea.contains(mouse)) {
                                    loadSong(displayList[i]);
                                    appState = AppState::Player;
                                    break;
                                }
                            }
                        }
                    }
                    else if (homeSubState == HomeSubState::ViewHistory) {
                        sf::FloatRect clearHistoryButtonRect(600, 50, 150, 30);
                        if (clearHistoryButtonRect.contains(mouse)) {
                            historyIndices.clear(); saveHistory(); cout << "Histori telah dibersihkan." << endl; scrollOffset = 0;
                            break;
                        }
                        int startHistoryIdx = scrollOffset; int endHistoryIdx = min((int)historyIndices.size(), startHistoryIdx + visibleSongs); int displayYOffset = 100;
                        for (int i = startHistoryIdx; i < endHistoryIdx; ++i) {
                            int displayPos = i - startHistoryIdx; int songIdx = historyIndices[i];
                            if (songIdx >= 0 && songIdx < library.size()) {
                                sf::FloatRect historyItemRect(50, displayYOffset + displayPos * 70, 700, 60);
                                if (historyItemRect.contains(mouse)) {
                                    loadSong(songIdx); appState = AppState::Player;
                                    break;
                                }
                            }
                        }
                    }
                    else if (homeSubState == HomeSubState::ViewQueue) {
                        sf::FloatRect clearQueueButtonRect(600, 50, 150, 30);
                        if (clearQueueButtonRect.contains(mouse)) {
                            clearQueue(); scrollOffset = 0;
                            break;
                        }
                        int startQueueIdx = scrollOffset; int endQueueIdx = min((int)songQueue.size(), startQueueIdx + visibleSongs); int displayYOffset = 100;
                        for (int i = startQueueIdx; i < endQueueIdx; ++i) {
                            int displayPos = i - startQueueIdx; int songIdx = songQueue[i];
                            if (songIdx >= 0 && songIdx < library.size()) {
                                sf::FloatRect queueItemRect(50, displayYOffset + displayPos * 70, 700, 60);
                                if (queueItemRect.contains(mouse)) {
                                    songQueue.erase(songQueue.begin() + i); loadSong(songIdx); appState = AppState::Player;
                                    break;
                                }
                            }
                        }
                    }
                    else if (homeSubState == HomeSubState::ViewPlaylists) {
                        // Tombol "Create New Playlist"
                        sf::FloatRect createPlaylistButtonRect(50, 80, 200, 30);
                        if (createPlaylistButtonRect.contains(mouse)) {
                            homeSubState = HomeSubState::CreateNewPlaylist;
                            newPlaylistName = ""; scrollOffset = 0;
                            break;
                        }
                        int startPlIdx = scrollOffset; int endPlIdx = min((int)playlists.size(), startPlIdx + visibleSongs); int displayYOffset = 150;
                        for (int i = startPlIdx; i < endPlIdx; ++i) {
                            int displayPos = i - startPlIdx;
                            sf::FloatRect playlistRect(50, displayYOffset + displayPos * 70, 650, 60);
                            sf::FloatRect deletePlaylistButtonRect(700, displayYOffset + displayPos * 70 + 15, 60, 30);
                            if (deletePlaylistButtonRect.contains(mouse)) {
                                deletePlaylist(i);
                                break;
                            }
                            else if (playlistRect.contains(mouse)) {
                                currentPlaylistViewIndex = i;
                                homeSubState = HomeSubState::ViewPlaylistContent;
                                scrollOffset = 0;
                                break;
                            }
                        }
                    }
                    else if (homeSubState == HomeSubState::CreateNewPlaylist) {
                    }
                    else if (homeSubState == HomeSubState::ViewPlaylistContent) {
                        sf::FloatRect backToPlaylistsButtonRect(50, 80, 100, 30);
                        if (backToPlaylistsButtonRect.contains(mouse)) {
                            homeSubState = HomeSubState::ViewPlaylists;
                            currentPlaylistViewIndex = -1; scrollOffset = 0;
                            break;
                        }
                        int startSongInPlIdx = scrollOffset; int endSongInPlIdx = min((int)playlists[currentPlaylistViewIndex].songIndices.size(), startSongInPlIdx + visibleSongs); int displayYOffset = 150;
                        for (int i = startSongInPlIdx; i < endSongInPlIdx; ++i) {
                            int displayPos = i - startSongInPlIdx; int songIdx = playlists[currentPlaylistViewIndex].songIndices[i];
                            if (songIdx >= 0 && songIdx < library.size()) {
                                sf::FloatRect songInPlRect(50, displayYOffset + displayPos * 70, 650, 60);
                                sf::FloatRect removeSongButtonRect(700, displayYOffset + displayPos * 70 + 15, 60, 30);

                                if (removeSongButtonRect.contains(mouse)) {
                                    removeSongFromPlaylist(currentPlaylistViewIndex, songIdx);
                                    break;
                                }
                                else if (songInPlRect.contains(mouse)) {
                                    loadSong(songIdx); appState = AppState::Player;
                                    break;
                                }
                            }
                        }
                    }

                    FloatRect scrollbarClickArea(770, 100, 10, 400); 
                    if (scrollbarClickArea.contains(mouse)) {
                        isDraggingScrollbar = true;
                        float clickPosRatio = (mouse.y - 100) / 400.f; 

                       
                        int maxScroll = 0;
                        if (homeSubState == HomeSubState::BrowseSongs) {
                            const auto& currentDisplayList = isSearching ? filteredIndices : recommendedIndices;
                            if (currentDisplayList.size() > visibleSongs) maxScroll = (int)currentDisplayList.size() - visibleSongs;
                        }
                        else if (homeSubState == HomeSubState::ViewHistory) {
                            if (historyIndices.size() > visibleSongs) maxScroll = (int)historyIndices.size() - visibleSongs;
                        }
                        else if (homeSubState == HomeSubState::ViewQueue) {
                            if (songQueue.size() > visibleSongs) maxScroll = (int)songQueue.size() - visibleSongs;
                        }
                        else if (homeSubState == HomeSubState::ViewPlaylists) {
                            if (playlists.size() > visibleSongs) maxScroll = (int)playlists.size() - visibleSongs;
                        }
                        else if (homeSubState == HomeSubState::ViewPlaylistContent && currentPlaylistViewIndex != -1) {
                            if (playlists[currentPlaylistViewIndex].songIndices.size() > visibleSongs) maxScroll = (int)playlists[currentPlaylistViewIndex].songIndices.size() - visibleSongs;
                        }

                        scrollOffset = round(clickPosRatio * maxScroll);
                        scrollOffset = max(0, min(scrollOffset, maxScroll));
                        break; 
                    }

                } 

                else if (appState == AppState::Player) {
                    sf::FloatRect backBtnRect(40, 40, 60, 30);
                    if (backBtnRect.contains(mouse)) {
                        appState = AppState::Home;                     
                        homeSubState = HomeSubState::BrowseSongs;
                        break;
                    }

                    
                    prevSprite.setPosition(260, 500); playSprite.setPosition(360, 500); pauseSprite.setPosition(360, 500);
                    nextSprite.setPosition(460, 500); repeatSprite.setPosition(560, 500);

                    sf::FloatRect playPauseRect;
                    if (isPlaying) { playPauseRect = pauseSprite.getGlobalBounds(); }
                    else { playPauseRect = playSprite.getGlobalBounds(); }
                    if (playPauseRect.contains(mouse)) { if (isPlaying) music.pause(); else music.play(); isPlaying = !isPlaying; break; }
                    if (nextSprite.getGlobalBounds().contains(mouse)) { if (!songQueue.empty()) playNextFromQueue(); else { currentSongIndex = (currentSongIndex + 1) % library.size(); loadSong(currentSongIndex); } isPlaying = true; break; }
                    if (prevSprite.getGlobalBounds().contains(mouse)) { currentSongIndex = (currentSongIndex - 1 + library.size()) % library.size(); loadSong(currentSongIndex); isPlaying = true; break; }
                    if (repeatSprite.getGlobalBounds().contains(mouse)) { isRepeating = !isRepeating; music.setLoop(isRepeating); cout << "Repeat is now: " << (isRepeating ? "ON" : "OFF") << endl; break; }
                    if (mouse.x >= 50 && mouse.x <= (50 + 700) && mouse.y >= 425 && mouse.y <= (425 + 10)) { float duration = music.getDuration().asSeconds(); if (duration > 0) { float clickPosition = (mouse.x - 50) / 700.f * duration; music.setPlayingOffset(sf::seconds(clickPosition)); } break; }
                    if (mouse.y >= 455 && mouse.y <= 465 && mouse.x >= 600 && mouse.x <= 750) { float newVolumeRatio = (mouse.x - 600) / 150.f; volume = max(0.f, min(100.f, newVolumeRatio * 100.f)); music.setVolume(volume); break; }
                }
            }

            else if (event.type == Event::MouseButtonReleased) {
                isDraggingScrollbar = false;
            }

            else if (event.type == Event::MouseMoved && isDraggingScrollbar && appState == AppState::Home) {
                Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
                float clickPosRatio = (mouse.y - 100) / 400.f;

                int maxScroll = 0;
                if (homeSubState == HomeSubState::BrowseSongs) {
                    const auto& currentDisplayList = isSearching ? filteredIndices : recommendedIndices;
                    if (currentDisplayList.size() > visibleSongs) {
                        maxScroll = (int)currentDisplayList.size() - visibleSongs;
                    }
                }
                else if (homeSubState == HomeSubState::ViewHistory) {
                    if (historyIndices.size() > visibleSongs) {
                        maxScroll = (int)historyIndices.size() - visibleSongs;
                    }
                }
                else if (homeSubState == HomeSubState::ViewQueue) {
                    if (songQueue.size() > visibleSongs) {
                        maxScroll = (int)songQueue.size() - visibleSongs;
                    }
                }
                else if (homeSubState == HomeSubState::ViewPlaylists) {
                    if (playlists.size() > visibleSongs) {
                        maxScroll = (int)playlists.size() - visibleSongs;
                    }
                }
                else if (homeSubState == HomeSubState::ViewPlaylistContent && currentPlaylistViewIndex != -1) {
                    if (playlists[currentPlaylistViewIndex].songIndices.size() > visibleSongs) {
                        maxScroll = (int)playlists[currentPlaylistViewIndex].songIndices.size() - visibleSongs;
                    }
                }

                scrollOffset = round(clickPosRatio * maxScroll);
                scrollOffset = max(0, min(scrollOffset, maxScroll));
            }
        }

        // --- Perbarui Status Lagu ---
        if (currentSongIndex != -1 && music.getStatus() == Music::Stopped && isPlaying) {
            if (!songQueue.empty()) {
                playNextFromQueue();
            }
            else if (!isRepeating) {
                currentSongIndex = (currentSongIndex + 1) % library.size();
                loadSong(currentSongIndex);
            }
        }

        // --- Proses Gambar ---
        window.clear(Color(30, 30, 30));

        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

        if (appState == AppState::Home) {
            RectangleShape browseBtn(Vector2f(150, 30));
            browseBtn.setPosition(50, 550);
            browseBtn.setFillColor(homeSubState == HomeSubState::BrowseSongs ? Color(255, 105, 180) : Color(199, 21, 133));
            FloatRect browseBtnRect(50, 550, 150, 30);
            if (browseBtnRect.contains(mousePos) && homeSubState != HomeSubState::BrowseSongs) {
                browseBtn.setFillColor(Color(255, 20, 147));
            }
            window.draw(browseBtn);
            Text browseText("Browse Songs", font, 16);
            browseText.setFillColor(Color::White);
            browseText.setPosition(browseBtn.getPosition().x + 10, browseBtn.getPosition().y + 5);
            window.draw(browseText);

            RectangleShape historyBtn(Vector2f(150, 30));
            historyBtn.setPosition(210, 550);
            historyBtn.setFillColor(homeSubState == HomeSubState::ViewHistory ? Color(255, 105, 180) : Color(199, 21, 133));
            FloatRect historyBtnRect(210, 550, 150, 30);
            if (historyBtnRect.contains(mousePos) && homeSubState != HomeSubState::ViewHistory) {
                historyBtn.setFillColor(Color(255, 20, 147));
            }
            window.draw(historyBtn);
            Text historyText("View History", font, 16);
            historyText.setFillColor(Color::White);
            historyText.setPosition(historyBtn.getPosition().x + 10, historyBtn.getPosition().y + 5);
            window.draw(historyText);

            RectangleShape queueBtn(Vector2f(150, 30));
            queueBtn.setPosition(370, 550);
            queueBtn.setFillColor(homeSubState == HomeSubState::ViewQueue ? Color(255, 105, 180) : Color(199, 21, 133));
            FloatRect queueBtnRect(370, 550, 150, 30);
            if (queueBtnRect.contains(mousePos) && homeSubState != HomeSubState::ViewQueue) {
                queueBtn.setFillColor(Color(255, 20, 147));
            }
            window.draw(queueBtn);
            Text queueText("View Queue", font, 16);
            queueText.setFillColor(Color::White);
            queueText.setPosition(queueBtn.getPosition().x + 10, queueBtn.getPosition().y + 5);
            window.draw(queueText);

            RectangleShape playlistBtn(Vector2f(150, 30));
            playlistBtn.setPosition(530, 550);
            playlistBtn.setFillColor((homeSubState == HomeSubState::ViewPlaylists || homeSubState == HomeSubState::CreateNewPlaylist || homeSubState == HomeSubState::ViewPlaylistContent) ? Color(255, 105, 180) : Color(199, 21, 133));
            FloatRect playlistBtnRect(530, 550, 150, 30);
            if (playlistBtnRect.contains(mousePos) && !(homeSubState == HomeSubState::ViewPlaylists || homeSubState == HomeSubState::CreateNewPlaylist || homeSubState == HomeSubState::ViewPlaylistContent)) {
                playlistBtn.setFillColor(Color(255, 20, 147));
            }
            window.draw(playlistBtn);
            Text playlistText("Playlists", font, 16);
            playlistText.setFillColor(Color::White);
            playlistText.setPosition(playlistBtn.getPosition().x + 10, playlistBtn.getPosition().y + 5);
            window.draw(playlistText);

            if (currentSongIndex != -1) {
                RectangleShape backToPlayerBtn(Vector2f(80, 30));
                backToPlayerBtn.setPosition(690, 550);
                backToPlayerBtn.setFillColor(Color(199, 21, 133));
                FloatRect backToPlayerButtonRect(690, 550, 80, 30);
                if (backToPlayerButtonRect.contains(mousePos)) {
                    backToPlayerBtn.setFillColor(Color(255, 20, 147));
                }
                window.draw(backToPlayerBtn);
                Text backToPlayerText("Player", font, 16);
                backToPlayerText.setFillColor(Color::White);
                backToPlayerText.setPosition(backToPlayerBtn.getPosition().x + 10, backToPlayerBtn.getPosition().y + 5);
                window.draw(backToPlayerText);
            }


            // --- Gambar Konten Berdasarkan Sub-State ---
            if (homeSubState == HomeSubState::BrowseSongs) {
                RectangleShape searchBar(Vector2f(700, 40));
                searchBar.setPosition(50, 40);
                searchBar.setFillColor(Color(70, 70, 70));
                window.draw(searchBar);

                Text searchText("Search: " + searchQuery, font, 20);
                searchText.setPosition(60, 45);
                searchText.setFillColor(Color::White);
                window.draw(searchText);

                const auto& displayList = isSearching ? filteredIndices : recommendedIndices;
                int startIdx = scrollOffset;
                int endIdx = min(startIdx + visibleSongs, (int)displayList.size());

                for (int i = startIdx; i < endIdx; ++i) {
                    int displayPos = i - startIdx;

                    RectangleShape songRect(Vector2f(700, 70));
                    songRect.setPosition(50, 100 + displayPos * 80);

                    if (currentSongIndex != -1 && displayList[i] == currentSongIndex && music.getStatus() == Music::Playing) {
                        songRect.setFillColor(Color(255, 105, 180));
                    }
                    else {
                        songRect.setFillColor(Color(60, 60, 60));
                    }
                    window.draw(songRect);

                    Sprite& sprToDraw = thumbnailSprites[displayList[i]];
                    sprToDraw.setPosition(60, 110 + displayPos * 80);
                    window.draw(sprToDraw);

                    Text titleText(library[displayList[i]].title, font, 18);
                    titleText.setPosition(120, 110 + displayPos * 80);
                    titleText.setFillColor(Color::White);
                    window.draw(titleText);

                    Text artistText(library[displayList[i]].artist, font, 14);
                    artistText.setPosition(120, 135 + displayPos * 80);
                    artistText.setFillColor(Color(220, 220, 220));
                    window.draw(artistText);

                    // Tombol "+q"
                    sf::RectangleShape addToQueueBtn(sf::Vector2f(40, 20));
                    addToQueueBtn.setPosition(610, 115 + displayPos * 80);
                    addToQueueBtn.setFillColor(sf::Color(70, 70, 70));
                    sf::FloatRect addToQueueButtonRect = addToQueueBtn.getGlobalBounds();
                    if (addToQueueButtonRect.contains(mousePos)) {
                        addToQueueBtn.setFillColor(sf::Color(200, 70, 130));
                    }
                    window.draw(addToQueueBtn);
                    sf::Text addQueueText("+q", font, 14);
                    addQueueText.setPosition(615, 117 + displayPos * 80);
                    addQueueText.setFillColor(sf::Color::White);
                    window.draw(addQueueText);

                    // Tombol "+p"
                    sf::RectangleShape addToPlaylistBtn(sf::Vector2f(40, 20));
                    addToPlaylistBtn.setPosition(655, 115 + displayPos * 80);
                    addToPlaylistBtn.setFillColor(sf::Color(70, 70, 70));
                    sf::FloatRect addToPlaylistButtonRect = addToPlaylistBtn.getGlobalBounds();
                    if (addToPlaylistButtonRect.contains(mousePos)) {
                        addToPlaylistBtn.setFillColor(sf::Color(200, 70, 130));
                    }
                    window.draw(addToPlaylistBtn);
                    sf::Text addPlaylistText("+p", font, 14);
                    addPlaylistText.setPosition(660, 117 + displayPos * 80);
                    addPlaylistText.setFillColor(sf::Color::White);
                    window.draw(addPlaylistText);
                }

                const auto& currentDisplayList = isSearching ? filteredIndices : recommendedIndices;
                if (currentDisplayList.size() > visibleSongs) {
                    float ratio = (float)visibleSongs / currentDisplayList.size();
                    float scrollbarHeight = ratio * 400;
                    float scrollbarY = 100 + (scrollOffset / float(currentDisplayList.size() - visibleSongs)) * (400 - scrollbarHeight);

                    RectangleShape scrollbar(Vector2f(10, scrollbarHeight));
                    scrollbar.setPosition(770, scrollbarY);
                    scrollbar.setFillColor(Color(255, 105, 180));
                    window.draw(scrollbar);
                }
            }
            else if (homeSubState == HomeSubState::ViewHistory) {
                Text historyHeader("Recently Played:", font, 24);
                historyHeader.setPosition(50, 40);
                historyHeader.setFillColor(Color::White);
                window.draw(historyHeader);

                RectangleShape clearHistoryButton(Vector2f(150, 30));
                clearHistoryButton.setPosition(600, 50);
                clearHistoryButton.setFillColor(Color(199, 21, 133));
                FloatRect clearHistoryButtonRect(600, 50, 150, 30);
                if (clearHistoryButtonRect.contains(mousePos)) {
                    clearHistoryButton.setFillColor(Color(255, 20, 147));
                }
                window.draw(clearHistoryButton);
                Text clearHistoryText("Clear History", font, 16);
                clearHistoryText.setPosition(610, 55);
                clearHistoryText.setFillColor(Color::White);
                window.draw(clearHistoryText);


                int historyDisplayY = 100;
                int startHistoryIdx = scrollOffset;
                int endHistoryIdx = min((int)historyIndices.size(), startHistoryIdx + visibleSongs);

                for (int i = startHistoryIdx; i < endHistoryIdx; ++i) {
                    int songIdx = historyIndices[i];
                    if (songIdx >= 0 && songIdx < library.size()) {
                        int displayPos = i - startHistoryIdx;
                        RectangleShape historyRect(Vector2f(700, 60));
                        historyRect.setPosition(50, historyDisplayY + displayPos * 70);
                        if (currentSongIndex != -1 && songIdx == currentSongIndex && music.getStatus() == Music::Playing) {
                            historyRect.setFillColor(Color(255, 105, 180));
                        }
                        else {
                            historyRect.setFillColor(Color(60, 60, 60));
                        }
                        window.draw(historyRect);

                        Text historySongTitle(library[songIdx].title, font, 18);
                        historySongTitle.setPosition(60, historyDisplayY + displayPos * 70 + 5);
                        historySongTitle.setFillColor(Color::White);
                        window.draw(historySongTitle);

                        Text historySongArtist(library[songIdx].artist, font, 14);
                        historySongArtist.setPosition(60, historyDisplayY + displayPos * 70 + 30);
                        historySongArtist.setFillColor(Color(220, 220, 220));
                        window.draw(historySongArtist);
                    }
                }

                if (historyIndices.size() > visibleSongs) {
                    float ratio = (float)visibleSongs / historyIndices.size();
                    float scrollbarHeight = ratio * 400;
                    float scrollbarY = 100 + (scrollOffset / float(historyIndices.size() - visibleSongs)) * (400 - scrollbarHeight);

                    RectangleShape scrollbar(Vector2f(10, scrollbarHeight));
                    scrollbar.setPosition(770, scrollbarY);
                    scrollbar.setFillColor(Color(255, 105, 180));
                    window.draw(scrollbar);
                }
            }
            else if (homeSubState == HomeSubState::ViewQueue) {
                Text queueHeader("Upcoming Queue:", font, 24);
                queueHeader.setPosition(50, 40);
                queueHeader.setFillColor(Color::White);
                window.draw(queueHeader);

                RectangleShape clearQueueButton(Vector2f(150, 30));
                clearQueueButton.setPosition(600, 50);
                clearQueueButton.setFillColor(Color(199, 21, 133));
                FloatRect clearQueueButtonRect(600, 50, 150, 30);
                if (clearQueueButtonRect.contains(mousePos)) {
                    clearQueueButton.setFillColor(Color(255, 20, 147));
                }
                window.draw(clearQueueButton);
                Text clearQueueText("Clear Queue", font, 16);
                clearQueueText.setPosition(610, 55);
                clearQueueText.setFillColor(Color::White);
                window.draw(clearQueueText);

                int queueDisplayY = 100;
                int startQueueIdx = scrollOffset;
                int endQueueIdx = min((int)songQueue.size(), startQueueIdx + visibleSongs);

                if (songQueue.empty()) {
                    Text emptyQueueText("Queue is empty.", font, 20);
                    emptyQueueText.setPosition(50, 150);
                    emptyQueueText.setFillColor(Color(150, 150, 150));
                    window.draw(emptyQueueText);
                }
                else {
                    for (int i = startQueueIdx; i < endQueueIdx; ++i) {
                        int songIdx = songQueue[i];
                        if (songIdx >= 0 && songIdx < library.size()) {
                            int displayPos = i - startQueueIdx;
                            RectangleShape queueRect(Vector2f(700, 60));
                            queueRect.setPosition(50, queueDisplayY + displayPos * 70);
                            queueRect.setFillColor(Color(60, 60, 60));
                            window.draw(queueRect);

                            Text queueSongTitle(library[songIdx].title, font, 18);
                            queueSongTitle.setPosition(60, queueDisplayY + displayPos * 70 + 5);
                            queueSongTitle.setFillColor(Color::White);
                            window.draw(queueSongTitle);

                            Text queueSongArtist(library[songIdx].artist, font, 14);
                            queueSongArtist.setPosition(60, queueDisplayY + displayPos * 70 + 30);
                            queueSongArtist.setFillColor(Color(220, 220, 220));
                            window.draw(queueSongArtist);
                        }
                    }

                    if (songQueue.size() > visibleSongs) {
                        float ratio = (float)visibleSongs / songQueue.size();
                        float scrollbarHeight = ratio * 400;
                        float scrollbarY = 100 + (scrollOffset / float(songQueue.size() - visibleSongs)) * (400 - scrollbarHeight);

                        RectangleShape scrollbar(Vector2f(10, scrollbarHeight));
                        scrollbar.setPosition(770, scrollbarY);
                        scrollbar.setFillColor(Color(255, 105, 180));
                        window.draw(scrollbar);
                    }
                }
            }
            else if (homeSubState == HomeSubState::ViewPlaylists) {
                Text playlistHeader("Your Playlists:", font, 24);
                playlistHeader.setPosition(50, 40);
                playlistHeader.setFillColor(Color::White);
                window.draw(playlistHeader);

                // Tombol "Create New Playlist"
                RectangleShape createPlaylistButton(Vector2f(200, 30));
                createPlaylistButton.setPosition(50, 80);
                createPlaylistButton.setFillColor(Color(199, 21, 133));
                FloatRect createPlaylistButtonRect(50, 80, 200, 30);
                if (createPlaylistButtonRect.contains(mousePos)) {
                    createPlaylistButton.setFillColor(Color(255, 20, 147));
                }
                window.draw(createPlaylistButton);
                Text createPlaylistText("Create New Playlist", font, 16);
                createPlaylistText.setFillColor(Color::White);
                createPlaylistText.setPosition(60, 85);
                window.draw(createPlaylistText);

                int playlistDisplayY = 150;
                int startPlIdx = scrollOffset;
                int endPlIdx = min((int)playlists.size(), startPlIdx + visibleSongs);

                if (playlists.empty()) {
                    Text emptyPlText("No playlists yet. Create one!", font, 20);
                    emptyPlText.setPosition(50, 200);
                    emptyPlText.setFillColor(Color(150, 150, 150));
                    window.draw(emptyPlText);
                }
                else {
                    for (int i = startPlIdx; i < endPlIdx; ++i) {
                        int displayPos = i - startPlIdx;
                        RectangleShape playlistRect(Vector2f(650, 60));
                        playlistRect.setPosition(50, playlistDisplayY + displayPos * 70);
                        playlistRect.setFillColor(Color(60, 60, 60));
                        FloatRect currentPlaylistRect(50, playlistDisplayY + displayPos * 70, 650, 60);
                        if (currentPlaylistRect.contains(mousePos)) {
                            playlistRect.setFillColor(Color(80, 80, 80));
                        }
                        window.draw(playlistRect);

                        Text playlistNameText(playlists[i].name, font, 18);
                        playlistNameText.setPosition(60, playlistDisplayY + displayPos * 70 + 5);
                        playlistNameText.setFillColor(Color::White);
                        window.draw(playlistNameText);

                        Text playlistCountText(to_string(playlists[i].songIndices.size()) + " songs", font, 14);
                        playlistCountText.setPosition(60, playlistDisplayY + displayPos * 70 + 30);
                        playlistCountText.setFillColor(Color(220, 220, 220));
                        window.draw(playlistCountText);

                        // Tombol Delete Playlist
                        RectangleShape deletePlaylistBtn(Vector2f(60, 30));
                        deletePlaylistBtn.setPosition(700, playlistDisplayY + displayPos * 70 + 15);
                        deletePlaylistBtn.setFillColor(Color(200, 50, 50));
                        FloatRect deletePlaylistButtonRect(700, playlistDisplayY + displayPos * 70 + 15, 60, 30);
                        if (deletePlaylistButtonRect.contains(mousePos)) {
                            deletePlaylistBtn.setFillColor(Color(255, 0, 0));
                        }
                        window.draw(deletePlaylistBtn);
                        Text deleteBtnText("Del", font, 16);
                        deleteBtnText.setFillColor(Color::White);
                        deleteBtnText.setPosition(715, playlistDisplayY + displayPos * 70 + 20);
                        window.draw(deleteBtnText);
                    }

                    if (playlists.size() > visibleSongs) {
                        float ratio = (float)visibleSongs / playlists.size();
                        float scrollbarHeight = ratio * 400;
                        float scrollbarY = 100 + (scrollOffset / float(playlists.size() - visibleSongs)) * (400 - scrollbarHeight);

                        RectangleShape scrollbar(Vector2f(10, scrollbarHeight));
                        scrollbar.setPosition(770, scrollbarY);
                        scrollbar.setFillColor(Color(255, 105, 180));
                        window.draw(scrollbar);
                    }
                }
            }

            else if (homeSubState == HomeSubState::CreateNewPlaylist) {
                Text createHeader("Create New Playlist", font, 24);
                createHeader.setPosition(50, 40);
                createHeader.setFillColor(Color::White);
                window.draw(createHeader);

                Text namePrompt("Enter playlist name:", font, 18);
                namePrompt.setPosition(50, 100);
                namePrompt.setFillColor(Color::White);
                window.draw(namePrompt);

                RectangleShape inputField(Vector2f(700, 40));
                inputField.setPosition(50, 140);
                inputField.setFillColor(Color(70, 70, 70));
                window.draw(inputField);

                Text inputText(newPlaylistName, font, 20);
                inputText.setPosition(60, 145);
                inputText.setFillColor(Color::White);
                window.draw(inputText);

                Text hintText("Press Enter to save, Esc to cancel.", font, 16);
                hintText.setPosition(50, 190);
                hintText.setFillColor(Color(150, 150, 150));
                window.draw(hintText);
            }

            else if (homeSubState == HomeSubState::ViewPlaylistContent && currentPlaylistViewIndex != -1) {
                Text playlistContentHeader("Playlist: " + playlists[currentPlaylistViewIndex].name, font, 24);
                playlistContentHeader.setPosition(50, 40);
                playlistContentHeader.setFillColor(Color::White);
                window.draw(playlistContentHeader);

                RectangleShape backButton(Vector2f(100, 30));
                backButton.setPosition(50, 80);
                backButton.setFillColor(Color(199, 21, 133));
                FloatRect backButtonRect(50, 80, 100, 30);
                if (backButtonRect.contains(mousePos)) {
                    backButton.setFillColor(Color(255, 20, 147));
                }
                window.draw(backButton);
                Text backText("Back", font, 16);
                backText.setFillColor(Color::White);
                backText.setPosition(60, 85);
                window.draw(backText);

                int songInPlDisplayY = 150;
                int startSongInPlIdx = scrollOffset;
                int endSongInPlIdx = min((int)playlists[currentPlaylistViewIndex].songIndices.size(), startSongInPlIdx + visibleSongs);

                if (playlists[currentPlaylistViewIndex].songIndices.empty()) {
                    Text emptyPlContentText("This playlist is empty. Add some songs from Browse Songs!", font, 20);
                    emptyPlContentText.setPosition(50, 200);
                    emptyPlContentText.setFillColor(Color(150, 150, 150));
                    window.draw(emptyPlContentText);
                }
                else {
                    for (int i = startSongInPlIdx; i < endSongInPlIdx; ++i) {
                        int displayPos = i - startSongInPlIdx;
                        int songIdx = playlists[currentPlaylistViewIndex].songIndices[i];
                        if (songIdx >= 0 && songIdx < library.size()) {
                            RectangleShape songInPlRect(Vector2f(650, 60));
                            songInPlRect.setPosition(50, songInPlDisplayY + displayPos * 70);
                            songInPlRect.setFillColor(Color(60, 60, 60));
                            FloatRect currentSongInPlRect(50, songInPlDisplayY + displayPos * 70, 650, 60);
                            if (currentSongInPlRect.contains(mousePos)) {
                                songInPlRect.setFillColor(Color(80, 80, 80));
                            }
                            window.draw(songInPlRect);

                            Text songInPlTitle(library[songIdx].title, font, 18);
                            songInPlTitle.setPosition(60, songInPlDisplayY + displayPos * 70 + 5);
                            songInPlTitle.setFillColor(Color::White);
                            window.draw(songInPlTitle);

                            Text songInPlArtist(library[songIdx].artist, font, 14);
                            songInPlArtist.setPosition(60, songInPlDisplayY + displayPos * 70 + 30);
                            songInPlArtist.setFillColor(Color(220, 220, 220));
                            window.draw(songInPlArtist);

                            RectangleShape removeSongBtn(Vector2f(60, 30));
                            removeSongBtn.setPosition(700, songInPlDisplayY + displayPos * 70 + 15);
                            removeSongBtn.setFillColor(Color(200, 50, 50));
                            FloatRect removeSongButtonRect(700, songInPlDisplayY + displayPos * 70 + 15, 60, 30);
                            if (removeSongButtonRect.contains(mousePos)) {
                                removeSongBtn.setFillColor(Color(255, 0, 0));
                            }
                            window.draw(removeSongBtn);
                            Text removeBtnText("X", font, 16);
                            removeBtnText.setFillColor(Color::White);
                            removeBtnText.setPosition(720, songInPlDisplayY + displayPos * 70 + 20);
                            window.draw(removeBtnText);
                        }
                    }

                    if (playlists[currentPlaylistViewIndex].songIndices.size() > visibleSongs) {
                        float ratio = (float)visibleSongs / playlists[currentPlaylistViewIndex].songIndices.size();
                        float scrollbarHeight = ratio * 400;
                        float scrollbarY = 100 + (scrollOffset / float(playlists[currentPlaylistViewIndex].songIndices.size() - visibleSongs)) * (400 - scrollbarHeight);

                        RectangleShape scrollbar(Vector2f(10, scrollbarHeight));
                        scrollbar.setPosition(770, scrollbarY);
                        scrollbar.setFillColor(Color(255, 105, 180));
                        window.draw(scrollbar);
                    }
                }
            }
        }
        else if (appState == AppState::Player) {
            if (currentSongIndex != -1) {
                window.draw(coverSprite);

                Text titleText(library[currentSongIndex].title, font, 24);
                titleText.setPosition(370, 100);
                titleText.setFillColor(Color::White);
                window.draw(titleText);

                Text artistText(library[currentSongIndex].artist, font, 20);
                artistText.setPosition(370, 140);
                artistText.setFillColor(Color(220, 220, 220));
                window.draw(artistText);

                float currentTime = music.getPlayingOffset().asSeconds();
                float totalTime = music.getDuration().asSeconds();
                float progress = totalTime > 0 ? currentTime / totalTime : 0;

                RectangleShape progressBarBg(Vector2f(700, 10));
                progressBarBg.setPosition(50, 425);
                progressBarBg.setFillColor(Color(70, 70, 70));
                window.draw(progressBarBg);

                RectangleShape progressBar(Vector2f(700 * progress, 10));
                progressBar.setPosition(50, 425);
                progressBar.setFillColor(Color(255, 105, 180));
                window.draw(progressBar);

                stringstream ss_current, ss_total;
                ss_current << setfill('0') << setw(2) << (int)(currentTime / 60) << ":" << setw(2) << (int)((int)currentTime % 60);
                Text timeText(ss_current.str(), font, 16);
                timeText.setPosition(50, 440);
                timeText.setFillColor(Color::White);
                window.draw(timeText);

                if (totalTime > 0) {
                    ss_total << setfill('0') << setw(2) << (int)(totalTime / 60) << ":" << setw(2) << (int)((int)totalTime % 60);
                    Text totalTimeText("/ " + ss_total.str(), font, 16);
                    totalTimeText.setPosition(timeText.getPosition().x + timeText.getLocalBounds().width + 5, 440);
                    totalTimeText.setFillColor(Color(180, 180, 180));
                    window.draw(totalTimeText);
                }

                prevSprite.setPosition(260, 500);
                if (prevSprite.getGlobalBounds().contains(mousePos)) {
                    prevSprite.setColor(Color(255, 140, 200));
                }
                else {
                    prevSprite.setColor(Color::White);
                }
                window.draw(prevSprite);

                if (isPlaying) {
                    pauseSprite.setPosition(360, 500);
                    if (pauseSprite.getGlobalBounds().contains(mousePos)) {
                        pauseSprite.setColor(Color(255, 140, 200));
                    }
                    else {
                        pauseSprite.setColor(Color::White);
                    }
                    window.draw(pauseSprite);
                }
                else {
                    playSprite.setPosition(360, 500);
                    if (playSprite.getGlobalBounds().contains(mousePos)) {
                        playSprite.setColor(Color(255, 140, 200));
                    }
                    else {
                        playSprite.setColor(Color::White);
                    }
                    window.draw(playSprite);
                }

                nextSprite.setPosition(460, 500);
                if (nextSprite.getGlobalBounds().contains(mousePos)) {
                    nextSprite.setColor(Color(255, 140, 200));
                }
                else {
                    nextSprite.setColor(Color::White);
                }
                window.draw(nextSprite);

                if (isRepeating) {
                    repeatSprite.setTexture(repeatOnTexture);
                }
                else {
                    repeatSprite.setTexture(repeatOffTexture);
                }
                repeatSprite.setPosition(560, 500);
                if (repeatSprite.getGlobalBounds().contains(mousePos)) {
                    repeatSprite.setColor(Color(255, 140, 200));
                }
                else {
                    repeatSprite.setColor(Color::White);
                }
                window.draw(repeatSprite);

                Text volumeLabel("Vol:", font, 16);
                volumeLabel.setPosition(550, 450);
                volumeLabel.setFillColor(Color::White);
                window.draw(volumeLabel);

                RectangleShape volumeBarBg(Vector2f(150, 10));
                volumeBarBg.setPosition(600, 455);
                volumeBarBg.setFillColor(Color(70, 70, 70));
                window.draw(volumeBarBg);

                RectangleShape volumeSlider(Vector2f(volume / 100.f * 150.f, 10));
                volumeSlider.setPosition(600, 455);
                volumeSlider.setFillColor(Color(255, 192, 203));
                window.draw(volumeSlider);

                Text volumeValueText(to_string((int)volume), font, 14);
                volumeValueText.setPosition(755, 450);
                volumeValueText.setFillColor(Color::White);
                window.draw(volumeValueText);

                RectangleShape backBtn(Vector2f(60, 30));
                backBtn.setPosition(40, 40);
                FloatRect backBtnRect(40, 40, 60, 30);
                if (backBtnRect.contains(mousePos)) backBtn.setFillColor(Color(255, 140, 200));
                else backBtn.setFillColor(Color(199, 21, 133));
                window.draw(backBtn);
                Text backText("Back", font, 16);
                backText.setFillColor(Color::White);
                backText.setPosition(50, 45);
                window.draw(backText);

                float currentPlaybackTime = music.getPlayingOffset().asSeconds();
                const auto& lyrics = library[currentSongIndex].syncedLyrics;

                int activeLyricIndex = -1;
                for (size_t i = 0; i < lyrics.size(); ++i) {
                    if (currentPlaybackTime >= lyrics[i].first) {
                        activeLyricIndex = i;
                    }
                    else {
                        break;
                    }
                }

                float targetActiveLyricY = 250.f;
                float lineHeight = 30.f;
                if (activeLyricIndex != -1) {
                    lyricsOffset = static_cast<int>((activeLyricIndex * lineHeight) - targetActiveLyricY);
                }
                else {
                    lyricsOffset = 0;
                }
                lyricsOffset = max(0, min(lyricsOffset, static_cast<int>((lyrics.size() * lineHeight) - (targetActiveLyricY + 100))));

                int linesToShow = 5;
                for (int i = 0; i < lyrics.size(); ++i) {
                    if (abs(i - activeLyricIndex) < linesToShow / 2 + 1) {
                        Text lyricText(lyrics[i].second, font, 20);
                        lyricText.setFillColor(Color::White);

                        if (i == activeLyricIndex) {
                            lyricText.setFillColor(Color(255, 105, 180));
                        }

                        lyricText.setPosition(550, targetActiveLyricY + (i - activeLyricIndex) * lineHeight);

                        if (lyricText.getPosition().y > 180 && lyricText.getPosition().y < 400) {
                            FloatRect lyricRect = lyricText.getLocalBounds();
                            lyricText.setOrigin(lyricRect.left + lyricRect.width / 2.0f, lyricRect.top + lyricRect.height / 2.0f);
                            window.draw(lyricText);
                        }
                    }
                }
            }
            else {
                Text noSongText("No song loaded. Go to Browse Songs.", font, 24);
                noSongText.setPosition(window.getSize().x / 2.f - noSongText.getLocalBounds().width / 2.f, window.getSize().y / 2.f - noSongText.getLocalBounds().height / 2.f);
                noSongText.setFillColor(Color::Red);
                window.draw(noSongText);
            }
        }

        if (showPlaylistSelectionPopup) {
            // Background semi-transparan
            RectangleShape overlay(Vector2f(window.getSize().x, window.getSize().y));
            overlay.setFillColor(Color(0, 0, 0, 150)); 
            window.draw(overlay);

            // Background pop-up
            RectangleShape popupBg(Vector2f(400, 300));
            popupBg.setPosition(200, 150);
            popupBg.setFillColor(Color(50, 50, 50)); 
            popupBg.setOutlineThickness(2);
            popupBg.setOutlineColor(Color(255, 105, 180)); 
            window.draw(popupBg);

            Text popupTitle("Add to Playlist:", font, 20);
            popupTitle.setFillColor(Color::White);
            popupTitle.setPosition(220, 160);
            window.draw(popupTitle);

            // Daftar playlist di pop-up
            if (playlists.empty()) {
                Text noPlaylistsText("No playlists available. Create one first!", font, 16);
                noPlaylistsText.setFillColor(Color(150, 150, 150));
                noPlaylistsText.setPosition(220, 200);
                window.draw(noPlaylistsText);
            }
            else {
                int numPlaylistsToShow = min((int)playlists.size(), 4); 
                for (int i = 0; i < numPlaylistsToShow; ++i) {
                    RectangleShape plEntryRect(Vector2f(380, 40));
                    plEntryRect.setPosition(210, 180 + i * 50);
                    plEntryRect.setFillColor(Color(70, 70, 70)); 

                    // Hover effect
                    FloatRect plEntryBounds(210, 180 + i * 50, 380, 40);
                    if (plEntryBounds.contains(mousePos)) {
                        plEntryRect.setFillColor(Color(90, 90, 90));
                    }
                    window.draw(plEntryRect);

                    Text plNameText(playlists[i].name, font, 18);
                    plNameText.setFillColor(Color::White);
                    plNameText.setPosition(220, 190 + i * 50);
                    window.draw(plNameText);
                }
            }

            // Tombol Cancel di pop-up
            RectangleShape cancelBtn(Vector2f(100, 30));
            cancelBtn.setPosition(350, 410);
            cancelBtn.setFillColor(Color(199, 21, 133));
            FloatRect cancelBtnRect(350, 410, 100, 30);
            if (cancelBtnRect.contains(mousePos)) {
                cancelBtn.setFillColor(Color(255, 20, 147));
            }
            window.draw(cancelBtn);
            Text cancelText("Cancel", font, 16);
            cancelText.setFillColor(Color::White);
            cancelText.setPosition(365, 415);
            window.draw(cancelText);
        }

        window.display();
    }

    return 0;
}