## System Design CAA - Solutii

#### 1. Your orgznization is running on a business-critical learning management system (LMS) on its own infrastructure on-premises. Since the platform has been growing exponentially, the stakeholders decided to migrate it to AWS. You are part of the development team and you are responsible for choosing the right services and designing the solution.
__The system enables teachers and experts to market, sell, and present their courses to people willing to learn from all around the world. Each course might contain written documents (mostly PDFs and PowerPoint presentations), videos, and images/diagrams. Other functional requirements include:__
- __students can be notified via email__
- __each course goes through a review process before being published__
- __teachers have access to the API of the system enabling them to publish the courses on their own websites__

<br>__The LMS is composed of several backend modules written in Java and Node.js, which store data in MySQL databases, while the frontend is built with React. Your team has been struggling lately to run the system locally due to its distributed nature and the increasing number of dependencies. Another important consideration is that the system transcodes the videos before the course is published in order to optimize bandwidth and playback.__
<br>__Since this is the core product of your organization, the main focus of the design must be the availability of the system and reducing operational/maintenance overhead. Of course, the cost must be optimized whenever possible.__
<br><br>_Describe your solution below. Mention which AWS services you would choose, how they communicate with each other, and, equally important, why you have chosen a particular service. Be as explicit as possible._
<br>_Optionally, you can upload images to illustrate your design (feel free to use any drawing or diagram tool you wish; images don't have to be pretty)._
<br><br>

> We would like to propose the following solution:
> * __EC2__, for hosting the React frontend, to allow for the scale of resources based on demand. Costs could also be reduced by using reserved instances.
> * __S3__, to store the course provided documents (PDFs, PPTs, videos, images). It is standard practice to use S3 for object storage, for its infinite space, and the cost-effective and secure operation.
> * __CloudFront__, AWS's CDN to serve content to the users from all around the world, depending on their location. CloudFront is fast, has a global network and edge locations and is preferred for cases when people from all around the world need to be able to access the system.
> * __Lambda__, to transcode the uploaded course. Lambda is serverless and on-demand and, therefore, we do not need to manage servers when there isn't demand for our transcoding functionality. Costs are determined based on the duration of its execution and the quantity of resources used, therefore minimal.
> * __SQS__ and __SNS Topics__, to send emails to students. They are reliable, cost-effective notification systems and do not require additional infrastructure.
> * __API Gateway__, for enabling teachers to make use of the API endpoints. It is a fully-managed service, easily-maintainable, making it easy for developers to handle APIs at any scale. Pricing is calculated based solely on the API calls received and the amount of data transfered, therefore it is a cost-effective solution.
> * __RDS__, to manage MySQL databases.
> * __Application Load Balancer__, to make the platform more efficient and provide a safety net in case of instance failure or downtime, redirecting traffic to available ones so that the service can remain available and not affect user experience.
> * __Cognito__, to manage users and their access. We can leverage Cognito user pool groups and roles to handle the different types of users/roles (students, teachers, experts) and the authorization of API calls on the Gateway based on their group. Cognito is reliable, scalable and can be configured with social logins, a convenient solution.

> In the future, the afore-mentioned solutions can be adjusted/tuned for cost and speed efficiency, should the platform grow for more traffic.
