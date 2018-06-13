<?php

$a = [
    "部队烧烤壮行宴",
    "部队",
    "烧烤",
    "壮行",
];

build_trie($a);

for ($i = 0; $i < 10000; $i++) {
    $str = "【部队烧烤“壮行宴”了解一下<img src=\"//img.t.sinajs.cn/t4/appstyle/expression/ext/normal/fa/2018new_chanzui_org.png\" title=\"[馋嘴]\"     alt=\"[馋嘴]\" class=\"face\" /><img src=\"//img.t.sinajs.cn/t4/appstyle/expression/ext/normal/fa/2018new_chanzui_org.png\" title=\"[馋嘴]\" alt=\"[馋嘴]    \" class=\"face\" />】6月9日，正值周末，中部战区空军地导某营官兵齐聚篮球场，一场别开生面的烧烤晚会即将拉开序幕。在该营即将接换新装、赴华北某地执行任务之际，为让大家在紧张训练之余更好放松身心，这顿广大官兵期盼已久的集体“壮行宴”应运而生。（杨杰 任俊吉 谭巳成 ";

    markred($str);
}

$str1 = "【部队烧烤“壮行宴”了解一下<img src=\"//img.t.sinajs.cn/t4/appstyle/expression/ext/normal/fa/2018new_chanzui_org.png\" title=\"[馋嘴]\"     alt=\"[馋嘴]\" class=\"face\" /><img src=\"//img.t.sinajs.cn/t4/appstyle/expression/ext/normal/fa/2018new_chanzui_org.png\" title=\"[馋嘴]\" alt=\"[馋嘴]    \" class=\"face\" />】6月9日，正值周末，中部战区空军地导某营官兵齐聚篮球场，一场别开生面的烧烤晚会即将拉开序幕。在该营即将接换新装、赴华北某地执行任务之际，为让大家在紧张训练之余更好放松身心，这顿广大官兵期盼已久的集体“壮行宴”应运而生。（杨杰 任俊吉 谭巳成 ";

echo markred($str1) . PHP_EOL;

