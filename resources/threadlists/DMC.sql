-- Kreuzstich
-- Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
-- MIT License, see LICENSE file.
-- 
-- -----------------------------------------------------------------------------
-- 
-- Generated based on DMC color card W100A Mouliné & Perlé:
-- - Mouliné Spécial 25 (Art. 117)
-- - Mouliné Color Variations (Art. 417F)
-- - Mouliné Effet Lumière (Art. 317W)
-- - Coton Perlé (Art. 115 - 116)
-- - Perlé Métallisé (Art. 315)
-- 
-- https://www.dmc.com/products/floss-color-card-mouline-pearl-cotton
-- 
-- Note #1: The color card W100A is not available anymore and has been replaced
--          by the newer version W100B with additional colors (as of 2026).
-- 
-- Note #2: Only the single-color threads for Mouliné & Perlé were included here.
--          Color Variations, Effet Lumière, Perlé Métallisé as well as
--          gradiant-color threads for Mouliné & Perlé have not been included.

INSERT INTO threadlists(user_id, name) VALUES(1, 'DMC');

-- 01
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 3713', 'DCB9B4'),
    ((SELECT id FROM list), 'DMC 761', 'DAA5A1'),
    ((SELECT id FROM list), 'DMC 760', 'D9827D'),
    ((SELECT id FROM list), 'DMC 3712', 'D75C53'),
    ((SELECT id FROM list), 'DMC 3328', 'CF3F35'),
    ((SELECT id FROM list), 'DMC 347', 'C81915'),
    ((SELECT id FROM list), 'DMC 353', 'E0B09A'),
    ((SELECT id FROM list), 'DMC 352', 'E28666'),
    ((SELECT id FROM list), 'DMC 351', 'E44426'),
    ((SELECT id FROM list), 'DMC 350', 'DC2A12'),
    ((SELECT id FROM list), 'DMC 349', 'D10D03'),
    ((SELECT id FROM list), 'DMC 817', 'C60B01'),
    ((SELECT id FROM list), 'DMC 3708', 'E28E93'),
    ((SELECT id FROM list), 'DMC 3706', 'E86A6B'),
    ((SELECT id FROM list), 'DMC 3705', 'E52F36'),
    ((SELECT id FROM list), 'DMC 3801', 'E01818'),
    ((SELECT id FROM list), 'DMC 666', 'D50502'),
    ((SELECT id FROM list), 'DMC 321', 'C9060F'),
    ((SELECT id FROM list), 'DMC 304', 'BB0B1B'),
    ((SELECT id FROM list), 'DMC 498', 'AC0C1D'),
    ((SELECT id FROM list), 'DMC 816', 'A40B15'),
    ((SELECT id FROM list), 'DMC 815', '84101D'),
    ((SELECT id FROM list), 'DMC 814', '6A101B')
;
-- 02
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 894', 'E5838E'),
    ((SELECT id FROM list), 'DMC 893', 'E55260'),
    ((SELECT id FROM list), 'DMC 892', 'EA3639'),
    ((SELECT id FROM list), 'DMC 891', 'E6252C'),
    ((SELECT id FROM list), 'DMC 818', 'D3B6AE'),
    ((SELECT id FROM list), 'DMC 957', 'E2828E'),
    ((SELECT id FROM list), 'DMC 956', 'E74B63'),
    ((SELECT id FROM list), 'DMC 309', 'C71D27'),
    ((SELECT id FROM list), 'DMC 963', 'D7ABAA'),
    ((SELECT id FROM list), 'DMC 3716', 'DA8890'),
    ((SELECT id FROM list), 'DMC 962', 'D36271'),
    ((SELECT id FROM list), 'DMC 961', 'D33B51'),
    ((SELECT id FROM list), 'DMC 3833', 'D74E5A'),
    ((SELECT id FROM list), 'DMC 3832', 'D32D35'),
    ((SELECT id FROM list), 'DMC 3831', 'C2131A'),
    ((SELECT id FROM list), 'DMC 777', 'A10C1D'),
    ((SELECT id FROM list), 'DMC 819', 'D2BCB1'),
    ((SELECT id FROM list), 'DMC 3326', 'D58184'),
    ((SELECT id FROM list), 'DMC 899', 'D44E5D'),
    ((SELECT id FROM list), 'DMC 335', 'D33342'),
    ((SELECT id FROM list), 'DMC 326', 'BA101A')
;
-- 03
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 151', 'CE979D'),
    ((SELECT id FROM list), 'DMC 3354', 'CA7C85'),
    ((SELECT id FROM list), 'DMC 3733', 'C85A6C'),
    ((SELECT id FROM list), 'DMC 3731', 'C33043'),
    ((SELECT id FROM list), 'DMC 3350', 'B21A2B'),
    ((SELECT id FROM list), 'DMC 150', 'AA0F1B'),
    ((SELECT id FROM list), 'DMC 3689', 'CC979F'),
    ((SELECT id FROM list), 'DMC 3688', 'BA5065'),
    ((SELECT id FROM list), 'DMC 3687', 'B62E49'),
    ((SELECT id FROM list), 'DMC 3803', '91192E'),
    ((SELECT id FROM list), 'DMC 3685', '7C1120'),
    ((SELECT id FROM list), 'DMC 605', 'CD8C94'),
    ((SELECT id FROM list), 'DMC 604', 'D17484'),
    ((SELECT id FROM list), 'DMC 603', 'D3576F'),
    ((SELECT id FROM list), 'DMC 602', 'D12645'),
    ((SELECT id FROM list), 'DMC 601', 'CA1532'),
    ((SELECT id FROM list), 'DMC 600', 'C30D28'),
    ((SELECT id FROM list), 'DMC 3806', 'C94662'),
    ((SELECT id FROM list), 'DMC 3805', 'C72248'),
    ((SELECT id FROM list), 'DMC 3804', 'C21237'),
    ((SELECT id FROM list), 'DMC 3609', 'C27E98'),
    ((SELECT id FROM list), 'DMC 3608', 'BD5E7F'),
    ((SELECT id FROM list), 'DMC 3607', 'B62A62'),
    ((SELECT id FROM list), 'DMC 718', 'A00E40'),
    ((SELECT id FROM list), 'DMC 917', '9C0C3B'),
    ((SELECT id FROM list), 'DMC 915', '750722')
;
-- 04
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 225', 'C5A094'),
    ((SELECT id FROM list), 'DMC 224', 'BE7E73'),
    ((SELECT id FROM list), 'DMC 152', 'B5665C'),
    ((SELECT id FROM list), 'DMC 223', 'A83D3B'),
    ((SELECT id FROM list), 'DMC 3722', '9D2C28'),
    ((SELECT id FROM list), 'DMC 3721', '8D1C19'),
    ((SELECT id FROM list), 'DMC 221', '721311'),
    ((SELECT id FROM list), 'DMC 778', 'B07874'),
    ((SELECT id FROM list), 'DMC 3727', 'AE6B71'),
    ((SELECT id FROM list), 'DMC 316', 'A24B60'),
    ((SELECT id FROM list), 'DMC 3726', '7E2C30'),
    ((SELECT id FROM list), 'DMC 315', '6C2124'),
    ((SELECT id FROM list), 'DMC 3802', '5F171D'),
    ((SELECT id FROM list), 'DMC 902', '5E0F18'),
    ((SELECT id FROM list), 'DMC 3743', '9A8388'),
    ((SELECT id FROM list), 'DMC 3042', '8B6C78'),
    ((SELECT id FROM list), 'DMC 3041', '5C3846'),
    ((SELECT id FROM list), 'DMC 3740', '522B37'),
    ((SELECT id FROM list), 'DMC 3836', '92526C'),
    ((SELECT id FROM list), 'DMC 3835', '72304E'),
    ((SELECT id FROM list), 'DMC 3834', '511A31'),
    ((SELECT id FROM list), 'DMC 154', '2F1421')
;
-- 05
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 211', 'A088A9'),
    ((SELECT id FROM list), 'DMC 210', '956BA0'),
    ((SELECT id FROM list), 'DMC 209', '89528E'),
    ((SELECT id FROM list), 'DMC 208', '652B78'),
    ((SELECT id FROM list), 'DMC 3837', '58236E'),
    ((SELECT id FROM list), 'DMC 327', '4C1F43'),
    ((SELECT id FROM list), 'DMC 153', 'A97A92'),
    ((SELECT id FROM list), 'DMC 554', 'A0628A'),
    ((SELECT id FROM list), 'DMC 553', '73316D'),
    ((SELECT id FROM list), 'DMC 552', '62235B'),
    ((SELECT id FROM list), 'DMC 550', '39143A'),
    ((SELECT id FROM list), 'DMC 3747', '8E8E9A'),
    ((SELECT id FROM list), 'DMC 341', '5C6F92'),
    ((SELECT id FROM list), 'DMC 156', '4A5A8B'),
    ((SELECT id FROM list), 'DMC 340', '4D4B8B'),
    ((SELECT id FROM list), 'DMC 155', '4C4186'),
    ((SELECT id FROM list), 'DMC 3746', '312B75'),
    ((SELECT id FROM list), 'DMC 333', '32246A'),
    ((SELECT id FROM list), 'DMC 157', '627B94'),
    ((SELECT id FROM list), 'DMC 794', '426085'),
    ((SELECT id FROM list), 'DMC 793', '304570'),
    ((SELECT id FROM list), 'DMC 3807', '212A5E'),
    ((SELECT id FROM list), 'DMC 792', '19215D'),
    ((SELECT id FROM list), 'DMC 158', '161C49'),
    ((SELECT id FROM list), 'DMC 791', '16153D')
;
-- 06
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 3840', '9FB1C8'),
    ((SELECT id FROM list), 'DMC 3839', '6C86BD'),
    ((SELECT id FROM list), 'DMC 3838', '4F6CB7'),
    ((SELECT id FROM list), 'DMC 800', '98B0C0'),
    ((SELECT id FROM list), 'DMC 809', '7999BD'),
    ((SELECT id FROM list), 'DMC 799', '598AB8'),
    ((SELECT id FROM list), 'DMC 798', '3461AF'),
    ((SELECT id FROM list), 'DMC 797', '273A8F'),
    ((SELECT id FROM list), 'DMC 796', '19257C'),
    ((SELECT id FROM list), 'DMC 820', '182171'),
    ((SELECT id FROM list), 'DMC 162', 'B2BEC1'),
    ((SELECT id FROM list), 'DMC 827', '96B0BE'),
    ((SELECT id FROM list), 'DMC 813', '6D98B6'),
    ((SELECT id FROM list), 'DMC 826', '3D78AF'),
    ((SELECT id FROM list), 'DMC 825', '285DA0'),
    ((SELECT id FROM list), 'DMC 824', '1F4587'),
    ((SELECT id FROM list), 'DMC 996', '3CA8D7'),
    ((SELECT id FROM list), 'DMC 3843', '0E97D7'),
    ((SELECT id FROM list), 'DMC 995', '007AD0'),
    ((SELECT id FROM list), 'DMC 3846', '30C2D4'),
    ((SELECT id FROM list), 'DMC 3845', '08B4D0'),
    ((SELECT id FROM list), 'DMC 3844', '009AC6')
;
-- 07
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 159', 'A2A3B3'),
    ((SELECT id FROM list), 'DMC 160', '7E87A7'),
    ((SELECT id FROM list), 'DMC 161', '5C6591'),
    ((SELECT id FROM list), 'DMC 3756', 'CDCCC1'),
    ((SELECT id FROM list), 'DMC 775', 'B9BFBE'),
    ((SELECT id FROM list), 'DMC 3841', 'ADBABF'),
    ((SELECT id FROM list), 'DMC 3325', '92ADBC'),
    ((SELECT id FROM list), 'DMC 3755', '729FBA'),
    ((SELECT id FROM list), 'DMC 334', '4F86AD'),
    ((SELECT id FROM list), 'DMC 322', '4672A7'),
    ((SELECT id FROM list), 'DMC 312', '22477F'),
    ((SELECT id FROM list), 'DMC 803', '1A3770'),
    ((SELECT id FROM list), 'DMC 336', '222C58'),
    ((SELECT id FROM list), 'DMC 823', '20203C'),
    ((SELECT id FROM list), 'DMC 939', '22202E'),
    ((SELECT id FROM list), 'DMC 3753', 'AFB2B1'),
    ((SELECT id FROM list), 'DMC 3752', '9CA6AC'),
    ((SELECT id FROM list), 'DMC 932', '80929B'),
    ((SELECT id FROM list), 'DMC 931', '4D697C'),
    ((SELECT id FROM list), 'DMC 930', '30485C'),
    ((SELECT id FROM list), 'DMC 3750', '25384F')
;
-- 08
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 828', 'A5B8B4'),
    ((SELECT id FROM list), 'DMC 3761', '94B6BB'),
    ((SELECT id FROM list), 'DMC 519', '74A5B7'),
    ((SELECT id FROM list), 'DMC 518', '3B86A6'),
    ((SELECT id FROM list), 'DMC 3760', '2B77A3'),
    ((SELECT id FROM list), 'DMC 517', '1B5A98'),
    ((SELECT id FROM list), 'DMC 3842', '124580'),
    ((SELECT id FROM list), 'DMC 311', '1B3764'),
    ((SELECT id FROM list), 'DMC 747', 'AFC1BC'),
    ((SELECT id FROM list), 'DMC 3766', '6AA6B1'),
    ((SELECT id FROM list), 'DMC 807', '388DA3'),
    ((SELECT id FROM list), 'DMC 3765', '17628F'),
    ((SELECT id FROM list), 'DMC 3811', '94B0AA'),
    ((SELECT id FROM list), 'DMC 598', '81A7A2'),
    ((SELECT id FROM list), 'DMC 597', '55939C'),
    ((SELECT id FROM list), 'DMC 3810', '3B838E'),
    ((SELECT id FROM list), 'DMC 3809', '1D6171'),
    ((SELECT id FROM list), 'DMC 3808', '14485B'),
    ((SELECT id FROM list), 'DMC 928', 'B0AD9D'),
    ((SELECT id FROM list), 'DMC 927', '959A8A'),
    ((SELECT id FROM list), 'DMC 926', '6A746D'),
    ((SELECT id FROM list), 'DMC 3768', '435257'),
    ((SELECT id FROM list), 'DMC 924', '294045'),
    ((SELECT id FROM list), 'DMC 3849', '4A9188'),
    ((SELECT id FROM list), 'DMC 3848', '257B74'),
    ((SELECT id FROM list), 'DMC 3847', '125652')
;
-- 09
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 964', '83BDAF'),
    ((SELECT id FROM list), 'DMC 959', '44AD9A'),
    ((SELECT id FROM list), 'DMC 958', '299E8B'),
    ((SELECT id FROM list), 'DMC 3812', '028B7E'),
    ((SELECT id FROM list), 'DMC 3851', '26A185'),
    ((SELECT id FROM list), 'DMC 943', '038E76'),
    ((SELECT id FROM list), 'DMC 3850', '018363'),
    ((SELECT id FROM list), 'DMC 993', '5A9F89'),
    ((SELECT id FROM list), 'DMC 992', '39937E'),
    ((SELECT id FROM list), 'DMC 3814', '187666'),
    ((SELECT id FROM list), 'DMC 991', '126453'),
    ((SELECT id FROM list), 'DMC 966', '87A47F'),
    ((SELECT id FROM list), 'DMC 564', '83A884'),
    ((SELECT id FROM list), 'DMC 563', '6DA07B'),
    ((SELECT id FROM list), 'DMC 562', '3E7F50'),
    ((SELECT id FROM list), 'DMC 505', '28613A'),
    ((SELECT id FROM list), 'DMC 3817', '7B967D'),
    ((SELECT id FROM list), 'DMC 3816', '50836A'),
    ((SELECT id FROM list), 'DMC 163', '35694B'),
    ((SELECT id FROM list), 'DMC 3815', '2E6648'),
    ((SELECT id FROM list), 'DMC 561', '1F4A35'),
    ((SELECT id FROM list), 'DMC 3813', '7B9279'),
    ((SELECT id FROM list), 'DMC 503', '5C8369'),
    ((SELECT id FROM list), 'DMC 502', '4C6B51'),
    ((SELECT id FROM list), 'DMC 501', '2A4636'),
    ((SELECT id FROM list), 'DMC 500', '222E25')
;
-- 10
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 955', '8AB488'),
    ((SELECT id FROM list), 'DMC 954', '62A26C'),
    ((SELECT id FROM list), 'DMC 913', '3F985F'),
    ((SELECT id FROM list), 'DMC 912', '2E8D55'),
    ((SELECT id FROM list), 'DMC 911', '13793D'),
    ((SELECT id FROM list), 'DMC 910', '0A622B'),
    ((SELECT id FROM list), 'DMC 909', '024F26'),
    ((SELECT id FROM list), 'DMC 3818', '0A3D25'),
    ((SELECT id FROM list), 'DMC 369', '96A16E'),
    ((SELECT id FROM list), 'DMC 368', '617C45'),
    ((SELECT id FROM list), 'DMC 320', '3C5C34'),
    ((SELECT id FROM list), 'DMC 367', '2C4729'),
    ((SELECT id FROM list), 'DMC 319', '1A2A1D'),
    ((SELECT id FROM list), 'DMC 890', '152417'),
    ((SELECT id FROM list), 'DMC 164', '6C924F'),
    ((SELECT id FROM list), 'DMC 989', '57742C'),
    ((SELECT id FROM list), 'DMC 988', '3A5F23'),
    ((SELECT id FROM list), 'DMC 987', '29441D'),
    ((SELECT id FROM list), 'DMC 986', '1E3316'),
    ((SELECT id FROM list), 'DMC 772', 'A5A765'),
    ((SELECT id FROM list), 'DMC 3348', '888735'),
    ((SELECT id FROM list), 'DMC 3347', '4B5A1D'),
    ((SELECT id FROM list), 'DMC 3346', '384516'),
    ((SELECT id FROM list), 'DMC 3345', '202D12'),
    ((SELECT id FROM list), 'DMC 895', '212D19')
;
-- 11
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 704', '8FBB4A'),
    ((SELECT id FROM list), 'DMC 703', '79B14E'),
    ((SELECT id FROM list), 'DMC 702', '4FA64D'),
    ((SELECT id FROM list), 'DMC 701', '37994E'),
    ((SELECT id FROM list), 'DMC 700', '1C8644'),
    ((SELECT id FROM list), 'DMC 699', '096F3C'),
    ((SELECT id FROM list), 'DMC 907', '97C32E'),
    ((SELECT id FROM list), 'DMC 906', '4BA41C'),
    ((SELECT id FROM list), 'DMC 905', '447F24'),
    ((SELECT id FROM list), 'DMC 904', '466A29'),
    ((SELECT id FROM list), 'DMC 472', 'C3C26F'),
    ((SELECT id FROM list), 'DMC 471', 'A1A34A'),
    ((SELECT id FROM list), 'DMC 470', '839A3D'),
    ((SELECT id FROM list), 'DMC 469', '6C7529'),
    ((SELECT id FROM list), 'DMC 937', '616F29'),
    ((SELECT id FROM list), 'DMC 936', '535A2F'),
    ((SELECT id FROM list), 'DMC 935', '4A4B35'),
    ((SELECT id FROM list), 'DMC 934', '403D2E'),
    ((SELECT id FROM list), 'DMC 523', '989C7B'),
    ((SELECT id FROM list), 'DMC 3053', 'A19F71'),
    ((SELECT id FROM list), 'DMC 3052', '919263'),
    ((SELECT id FROM list), 'DMC 3051', '616033'),
    ((SELECT id FROM list), 'DMC 524', 'ADA88B'),
    ((SELECT id FROM list), 'DMC 522', '929B81'),
    ((SELECT id FROM list), 'DMC 520', '475A3F')
;
-- 12
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 3364', '8E975F'),
    ((SELECT id FROM list), 'DMC 3363', '6A8156'),
    ((SELECT id FROM list), 'DMC 3362', '4E613B'),
    ((SELECT id FROM list), 'DMC 165', 'D0C767'),
    ((SELECT id FROM list), 'DMC 3819', 'D1C950'),
    ((SELECT id FROM list), 'DMC 166', 'C1B922'),
    ((SELECT id FROM list), 'DMC 581', '919A2C'),
    ((SELECT id FROM list), 'DMC 580', '827422'),
    ((SELECT id FROM list), 'DMC 734', 'C6AB43'),
    ((SELECT id FROM list), 'DMC 733', 'B19629'),
    ((SELECT id FROM list), 'DMC 732', '886A18'),
    ((SELECT id FROM list), 'DMC 730', '765E1E'),
    ((SELECT id FROM list), 'DMC 3013', 'B5A670'),
    ((SELECT id FROM list), 'DMC 3012', '97813D'),
    ((SELECT id FROM list), 'DMC 3011', '7B6632'),
    ((SELECT id FROM list), 'DMC 372', 'B8A06B'),
    ((SELECT id FROM list), 'DMC 371', 'AF8E46'),
    ((SELECT id FROM list), 'DMC 370', 'AE8C3F'),
    ((SELECT id FROM list), 'DMC 834', 'CFAF52'),
    ((SELECT id FROM list), 'DMC 833', 'C79D31'),
    ((SELECT id FROM list), 'DMC 832', 'BD8517'),
    ((SELECT id FROM list), 'DMC 831', '9F6F1B'),
    ((SELECT id FROM list), 'DMC 830', '8A5516'),
    ((SELECT id FROM list), 'DMC 829', '8D4D18')
;
-- 13
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 613', 'C5B291'),
    ((SELECT id FROM list), 'DMC 612', 'B59460'),
    ((SELECT id FROM list), 'DMC 611', '91693F'),
    ((SELECT id FROM list), 'DMC 610', '94693C'),
    ((SELECT id FROM list), 'DMC 3047', 'D2BC8B'),
    ((SELECT id FROM list), 'DMC 3046', 'C6A65D'),
    ((SELECT id FROM list), 'DMC 3045', 'B67C3B'),
    ((SELECT id FROM list), 'DMC 167', 'AC6B31'),
    ((SELECT id FROM list), 'DMC 746', 'D3C4A6'),
    ((SELECT id FROM list), 'DMC 677', 'D3BB87'),
    ((SELECT id FROM list), 'DMC 422', 'C19154'),
    ((SELECT id FROM list), 'DMC 3828', 'B2722B'),
    ((SELECT id FROM list), 'DMC 420', '9F5217'),
    ((SELECT id FROM list), 'DMC 869', '874115'),
    ((SELECT id FROM list), 'DMC 728', 'E3A31C'),
    ((SELECT id FROM list), 'DMC 783', 'D7800B'),
    ((SELECT id FROM list), 'DMC 782', 'C05D07'),
    ((SELECT id FROM list), 'DMC 780', 'AF4105'),
    ((SELECT id FROM list), 'DMC 676', 'D7A959'),
    ((SELECT id FROM list), 'DMC 729', 'CC8521'),
    ((SELECT id FROM list), 'DMC 680', 'B66C16'),
    ((SELECT id FROM list), 'DMC 3829', 'B05D0D'),
    ((SELECT id FROM list), 'DMC 3822', 'DEB443'),
    ((SELECT id FROM list), 'DMC 3821', 'DBA728'),
    ((SELECT id FROM list), 'DMC 3820', 'D79912'),
    ((SELECT id FROM list), 'DMC 3852', 'CC8508')
;
-- 14
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 445', 'DED361'),
    ((SELECT id FROM list), 'DMC 307', 'EED20B'),
    ((SELECT id FROM list), 'DMC 973', 'F3CA08'),
    ((SELECT id FROM list), 'DMC 444', 'EFC100'),
    ((SELECT id FROM list), 'DMC 3078', 'D8C582'),
    ((SELECT id FROM list), 'DMC 727', 'E1C65A'),
    ((SELECT id FROM list), 'DMC 726', 'E8BD29'),
    ((SELECT id FROM list), 'DMC 725', 'E7AC1B'),
    ((SELECT id FROM list), 'DMC 972', 'F09500'),
    ((SELECT id FROM list), 'DMC 745', 'D9B979'),
    ((SELECT id FROM list), 'DMC 744', 'E2B74A'),
    ((SELECT id FROM list), 'DMC 743', 'ECB01F'),
    ((SELECT id FROM list), 'DMC 742', 'F09400'),
    ((SELECT id FROM list), 'DMC 741', 'F27100'),
    ((SELECT id FROM list), 'DMC 740', 'F55600'),
    ((SELECT id FROM list), 'DMC 970', 'F85400'),
    ((SELECT id FROM list), 'DMC 947', 'F13600'),
    ((SELECT id FROM list), 'DMC 946', 'E32E00'),
    ((SELECT id FROM list), 'DMC 900', 'C71700'),
    ((SELECT id FROM list), 'DMC 967', 'D99776'),
    ((SELECT id FROM list), 'DMC 3824', 'DE7F55'),
    ((SELECT id FROM list), 'DMC 3341', 'E46430'),
    ((SELECT id FROM list), 'DMC 3340', 'EB470A'),
    ((SELECT id FROM list), 'DMC 608', 'F01D00'),
    ((SELECT id FROM list), 'DMC 606', 'DC0B00')
;
-- 15
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 951', 'CDA888'),
    ((SELECT id FROM list), 'DMC 3856', 'D4965D'),
    ((SELECT id FROM list), 'DMC 722', 'E46E21'),
    ((SELECT id FROM list), 'DMC 721', 'E04704'),
    ((SELECT id FROM list), 'DMC 720', 'D32C00'),
    ((SELECT id FROM list), 'DMC 3825', 'DE813A'),
    ((SELECT id FROM list), 'DMC 922', 'D0460B'),
    ((SELECT id FROM list), 'DMC 921', 'C13105'),
    ((SELECT id FROM list), 'DMC 920', 'A91D02'),
    ((SELECT id FROM list), 'DMC 919', '9A1301'),
    ((SELECT id FROM list), 'DMC 918', '8A1608'),
    ((SELECT id FROM list), 'DMC 3770', 'CAAD93'),
    ((SELECT id FROM list), 'DMC 945', 'C6946B'),
    ((SELECT id FROM list), 'DMC 402', 'D27431'),
    ((SELECT id FROM list), 'DMC 3776', 'C2430D'),
    ((SELECT id FROM list), 'DMC 301', 'A42C06'),
    ((SELECT id FROM list), 'DMC 400', '7F1B04'),
    ((SELECT id FROM list), 'DMC 300', '651A0B'),
    ((SELECT id FROM list), 'DMC 3823', 'CCB783'),
    ((SELECT id FROM list), 'DMC 3855', 'DAA649'),
    ((SELECT id FROM list), 'DMC 3854', 'DB7716'),
    ((SELECT id FROM list), 'DMC 3853', 'D14A01')
;
-- 16
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 3827', 'D59E5C'),
    ((SELECT id FROM list), 'DMC 977', 'DA9036'),
    ((SELECT id FROM list), 'DMC 976', 'CF6B14'),
    ((SELECT id FROM list), 'DMC 3826', 'BD5112'),
    ((SELECT id FROM list), 'DMC 975', '993716'),
    ((SELECT id FROM list), 'DMC 948', 'CEB3A4'),
    ((SELECT id FROM list), 'DMC 754', 'D2A187'),
    ((SELECT id FROM list), 'DMC 3771', 'D29875'),
    ((SELECT id FROM list), 'DMC 758', 'CF8E71'),
    ((SELECT id FROM list), 'DMC 3778', 'C96649'),
    ((SELECT id FROM list), 'DMC 356', 'C14E34'),
    ((SELECT id FROM list), 'DMC 3830', 'BA331F'),
    ((SELECT id FROM list), 'DMC 355', 'A72015'),
    ((SELECT id FROM list), 'DMC 3777', '931B14'),
    ((SELECT id FROM list), 'DMC 3779', 'CC9480'),
    ((SELECT id FROM list), 'DMC 3859', 'B35F48'),
    ((SELECT id FROM list), 'DMC 3858', '822A23'),
    ((SELECT id FROM list), 'DMC 3857', '69201C'),
    ((SELECT id FROM list), 'DMC 3774', 'CAAA96'),
    ((SELECT id FROM list), 'DMC 950', 'C7A48D'),
    ((SELECT id FROM list), 'DMC 3064', 'BB7050'),
    ((SELECT id FROM list), 'DMC 407', 'B87256'),
    ((SELECT id FROM list), 'DMC 3772', 'A8533A'),
    ((SELECT id FROM list), 'DMC 632', '923C2A')
;
-- 17
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 453', 'ACA09C'),
    ((SELECT id FROM list), 'DMC 452', '9C8584'),
    ((SELECT id FROM list), 'DMC 451', '836564'),
    ((SELECT id FROM list), 'DMC 3861', '936965'),
    ((SELECT id FROM list), 'DMC 3860', '70423E'),
    ((SELECT id FROM list), 'DMC 779', '60342F'),
    ((SELECT id FROM list), 'DMC 712', 'C4BAA7'),
    ((SELECT id FROM list), 'DMC 739', 'C4B397'),
    ((SELECT id FROM list), 'DMC 738', 'C1A172'),
    ((SELECT id FROM list), 'DMC 437', 'C08E50'),
    ((SELECT id FROM list), 'DMC 436', 'BD702D'),
    ((SELECT id FROM list), 'DMC 435', 'B2591A'),
    ((SELECT id FROM list), 'DMC 434', '983A11'),
    ((SELECT id FROM list), 'DMC 433', '782B12'),
    ((SELECT id FROM list), 'DMC 801', '632718'),
    ((SELECT id FROM list), 'DMC 898', '572618'),
    ((SELECT id FROM list), 'DMC 938', '43211A'),
    ((SELECT id FROM list), 'DMC 3371', '28201C'),
    ((SELECT id FROM list), 'DMC 543', 'BEA795'),
    ((SELECT id FROM list), 'DMC 3864', 'AF8466'),
    ((SELECT id FROM list), 'DMC 3863', '985B3C'),
    ((SELECT id FROM list), 'DMC 3862', '884828'),
    ((SELECT id FROM list), 'DMC 3031', '442820')
;
-- 18
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC B5200', 'C7C8CE'),
    ((SELECT id FROM list), 'DMC BLANC', 'C7C8C5'),
    ((SELECT id FROM list), 'DMC 3865', 'C5C5BE'),
    ((SELECT id FROM list), 'DMC ECRU', 'C1B6A0'),
    ((SELECT id FROM list), 'DMC 822', 'B7AD95'),
    ((SELECT id FROM list), 'DMC 644', 'A59B84'),
    ((SELECT id FROM list), 'DMC 642', '867355'),
    ((SELECT id FROM list), 'DMC 640', '645B3F'),
    ((SELECT id FROM list), 'DMC 3787', '493C31'),
    ((SELECT id FROM list), 'DMC 3021', '3B2D26'),
    ((SELECT id FROM list), 'DMC 3024', 'A1A195'),
    ((SELECT id FROM list), 'DMC 3023', '897F66'),
    ((SELECT id FROM list), 'DMC 3022', '676B51'),
    ((SELECT id FROM list), 'DMC 535', '463D3A'),
    ((SELECT id FROM list), 'DMC 3033', 'B29C83'),
    ((SELECT id FROM list), 'DMC 3782', '9D7D5C'),
    ((SELECT id FROM list), 'DMC 3032', '876D49'),
    ((SELECT id FROM list), 'DMC 3790', '734C33'),
    ((SELECT id FROM list), 'DMC 3781', '523124'),
    ((SELECT id FROM list), 'DMC 3866', 'B6AB9D'),
    ((SELECT id FROM list), 'DMC 842', 'AC876C'),
    ((SELECT id FROM list), 'DMC 841', '93654A'),
    ((SELECT id FROM list), 'DMC 840', '7C4B34'),
    ((SELECT id FROM list), 'DMC 839', '502C21'),
    ((SELECT id FROM list), 'DMC 838', '3C241E')
;
-- 19
WITH list AS (SELECT id FROM threadlists WHERE user_id = 1 AND name = 'DMC')
INSERT INTO threads(list_id,name,color) VALUES
    ((SELECT id FROM list), 'DMC 3072', 'A2A79D'),
    ((SELECT id FROM list), 'DMC 648', '908A7D'),
    ((SELECT id FROM list), 'DMC 647', '777866'),
    ((SELECT id FROM list), 'DMC 646', '63584A'),
    ((SELECT id FROM list), 'DMC 645', '4B423D'),
    ((SELECT id FROM list), 'DMC 844', '3B3130'),
    ((SELECT id FROM list), 'DMC 762', 'ABABAB'),
    ((SELECT id FROM list), 'DMC 415', '8C8D94'),
    ((SELECT id FROM list), 'DMC 318', '727181'),
    ((SELECT id FROM list), 'DMC 414', '585664'),
    ((SELECT id FROM list), 'DMC 168', '878C8F'),
    ((SELECT id FROM list), 'DMC 169', '5E6467'),
    ((SELECT id FROM list), 'DMC 317', '403F4D'),
    ((SELECT id FROM list), 'DMC 413', '34353B'),
    ((SELECT id FROM list), 'DMC 3799', '2D2A2C'),
    ((SELECT id FROM list), 'DMC 310', '1D1C1C')
;
